//
// Created by val on 3/21/25.
//

#include "slot_reel.hpp"

#include <random>

#include "random_gen.hpp"

namespace SlotMachine {

    void SlotReel::initializeSymbols(const int &amount) {
        symbols.reserve(amount + 1);

        for (int i = 0; i <= amount; i++) {
            symbols.emplace_back();
        }
    }

    SlotReel::SlotReel() {
        initializeSymbols(Config::DEFAULT_SYMBOL_AMOUNT);

        if (Config::RANDOMIZE_SPIN_SPEED) {
            this->spinSpeed = RandomGen::getRandomSpinSpeed();
        }
    }

    SlotReel::SlotReel(const int &amount) {
        initializeSymbols(amount);
        if (Config::RANDOMIZE_SPIN_SPEED) {
            this->spinSpeed = RandomGen::getRandomSpinSpeed();
        }
    }

    void SlotReel::update(float deltaTime) {
        if (spinning) {
            currentPosition = currentPosition + spinSpeed * deltaTime;
            currentPosition = std::fmod(currentPosition, static_cast<float>(symbols.size()));
            if (currentPosition >= stopTarget) {
                spinning = false;
                currentPosition = stopTarget;
            }
        }
    }
} //SlotMachine
