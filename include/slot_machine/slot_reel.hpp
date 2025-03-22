//
// Created by val on 3/21/25.
//

#pragma once

#include <vector>
#include "slot_symbol.hpp"
#include "config_values.hpp"

namespace SlotMachine {
    class SlotReel {
    private:
        std::vector<SlotSymbol> symbols;
        float spinSpeed = Config::DEFAULT_SPIN_SPEED;
        bool spinning = false;

        ///Current position is corresponding to index of the current topmost symbol, but fractional
        float currentPosition = 0;
        int stopTarget = 1e9;

        void initializeSymbols(const int &amount);

    public:
        SlotReel();

        SlotReel(const int &amount);

        /// Starts spinning until stopSpinning() gets called
        void startSpinning() {
            spinning = true;
            stopTarget = 1e9;
        }

        /// Spins to the next position and then sets spinning=false
        void stopSpinning() {
            stopTarget = static_cast<int>(currentPosition) + 1;
        }

        [[nodiscard]] bool isSpinning() const { return spinning; }

        /// Moves currentPosition based on spinSpeed
        void update(float deltaTime);

        [[nodiscard]] float getPosition() const {
            return currentPosition;
        };

        [[nodiscard]] const SlotSymbol &getSymbol(size_t index) const {
            return symbols[index % symbols.size()]; //mod in case index is bigger than size like in calculateWin()
        }

        [[nodiscard]] ESlotSymbolType getCurrentSymbolType() const {
            return symbols[static_cast<size_t>(currentPosition)].getType();
        }

        [[nodiscard]] size_t getSymbolCount() const { return symbols.size(); }
    };
} //SlotMachine
