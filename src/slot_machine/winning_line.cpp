//
// Created by val on 3/23/25.
//

#include "winning_line.hpp"
#include "slot_symbol_type.hpp"
#include <array>

namespace SlotMachine {
    void WinningLine::initializeLine(size_t reelCount, const sf::Vector2f &boundsPos) {
        //If line is straight only it can be drawn as a rectangle but diagonal lines are supported too
        //So VertexArray is needed
        line = sf::VertexArray(sf::PrimitiveType::LineStrip, reelCount);
        for (int i = 0; i < reelCount; i++) {
            line[i].position = sf::Vector2f({i*Config::REEL_WIDTH + boundsPos.x + Config::SYMBOL_SIZE/2,
                pattern[i%pattern.size()]*Config::SYMBOL_SIZE+boundsPos.y + Config::SYMBOL_SIZE/2});
            line[i].color = color;
        }
        lineInitialized = true;
    }

    int WinningLine::calculateWin(const std::vector<SlotReel> &reels) {
        int res = 0;
        std::array<int, static_cast<int>(ESlotSymbolType::TypesCount)> count = {};
        for (size_t i = 0; i < reels.size(); i++) {
            ESlotSymbolType type = reels[i].getSymbol(reels[i].getPosition() + pattern[i%pattern.size()]).getType();
            count[static_cast<int>(type)]++;
        }
        for (size_t i = 0; i < count.size(); i++) {
            if (count[i] > reels.size()/2) {
                res+=count[i]*SymbolTypeToValueMap.at(static_cast<ESlotSymbolType>(i));
                won=true;
            }
        }
        return res;
    }

    void WinningLine::draw(sf::RenderTarget &window, const std::vector<SlotReel> &reels) {
        if (won) {
            if (!lineInitialized) {
                sf::Vector2f boundsPos = window.getView().getCenter() - window.getView().getSize()/2.f;
                initializeLine(reels.size(), boundsPos);
            }
            window.draw(line);
        }
    }
} // SlotMachine