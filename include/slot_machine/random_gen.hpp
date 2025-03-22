//
// Created by val on 3/22/25.
//

#pragma once
#include <random>
#include "slot_symbol_type.hpp"
#include "config_values.hpp"

namespace SlotMachine {
    /// Helper class to keep static random_device and mt gen.
    class RandomGen {
    public:
        static std::mt19937 &getGenerator() {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            return gen;
        }

        static ESlotSymbolType getRandomType() {
            static std::uniform_int_distribution<int> dist_i(0, static_cast<int>(ESlotSymbolType::TypesCount) - 1);
            return static_cast<ESlotSymbolType>(dist_i(getGenerator()));
        }

        static float getRandomSpinSpeed() {
            static std::uniform_real_distribution<float> dist_f(Config::MIN_SPIN_SPEED, Config::MAX_SPIN_SPEED);
            return dist_f(getGenerator());
        }
    };
}
