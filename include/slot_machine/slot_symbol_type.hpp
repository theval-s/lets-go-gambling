#pragma once
#include <unordered_map>

namespace SlotMachine {
    /// SlotSymbolTypes, based on textures in ./resources folder. Adding or removing textures there requires to modify this enum, and SlotView::loadTextures();
    enum class ESlotSymbolType {
        Banana = 0, Bell, Cherry, Coin, Diamond, Seven, Star, Watermelon, TypesCount
    };

    /// Maps symbol types to their values, used for score calculation
    const std::unordered_map<ESlotSymbolType, int> SymbolTypeToValueMap = {
        {ESlotSymbolType::Banana, 50},
        {ESlotSymbolType::Bell, 25},
        {ESlotSymbolType::Cherry, 10},
        {ESlotSymbolType::Coin, 50},
        {ESlotSymbolType::Diamond, 100},
        {ESlotSymbolType::Seven, 150},
        {ESlotSymbolType::Star, 75},
        {ESlotSymbolType::Watermelon, 25}
    };
}
