//
// Created by val on 3/21/25.
//

#pragma once

#include "random_gen.hpp"
#include "slot_symbol_type.hpp"

namespace SlotMachine {
    class SlotSymbol {
    private:
        ESlotSymbolType type;

    public:
        ///@brief Creates random SlotSymbol
        SlotSymbol() {
            type = RandomGen::getRandomType();
        };

        ///@brief Creates SlotSymbol with symbol type
        explicit SlotSymbol(const ESlotSymbolType &symbol);

        [[nodiscard]] ESlotSymbolType getType() const { return type; }
    };
} //SlotMachine
