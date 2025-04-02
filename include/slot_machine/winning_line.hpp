//
// Created by val on 3/23/25.
//

#pragma once
#include "slot_reel.hpp"
#include <vector>
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/VertexArray.hpp"

namespace SlotMachine {



class WinningLine {
private:
    ///Patterns define exact positions that are counted for wins
    ///And patterns are repeated over the whole slot machine
    ///For example: simple pattern of 3 will count all symbols on line 3
    ///Pattern of {3,2,4} will check reels[0] at 3, reels[1] at 2, reels[2] at 4 and then again reels[3] at 3 and so on
    ///Lines count starts at 0
    std::vector<size_t> pattern;
    bool won = false;

    //Line depends on amount of reels, so we create it during first draw call and then reuse it
    sf::Color color;
    sf::VertexArray line;
    bool lineInitialized = false;

    void initializeLine(size_t reelCount, const sf::Vector2f &boundsPos);

public:
    explicit WinningLine(size_t pos, const sf::Color &lineColor=sf::Color::Black) : pattern(1,pos), color(lineColor) {
    }

    explicit WinningLine(const std::vector<size_t> &pattern, sf::Color lineColor=sf::Color::Black) : pattern(pattern), color(lineColor){};

    ///@brief Calculates and return win score and sets won=true if there is a win on this line
    ///Win is accounted when more than reels.size()/2 same symbols are on a pattern,
    ///and value is equal to symbol value*amount
    ///@param reels slot reels to check for win
    int calculateWin(const std::vector<SlotReel> &reels);
    void draw (sf::RenderTarget &window, const std::vector<SlotReel> &reels);
    void disableWinState() { won = false; }
    // void setWinningLine(const size_t &pos);
};

} // SlotMachine
