//
// Created by val on 3/19/25.
//

#pragma once

#include <SFML/Graphics.hpp>

#include "slot_reel.hpp"
#include "slot_view.hpp"
#include "config_values.hpp"
#include "winning_line.hpp"

namespace SlotMachine {
    /// Main class for slot machine. Stores reels, renderer, bounds for rendering view
    class Machine {
    private:
        std::vector<SlotReel> reels;
        SlotView slotView;
        sf::FloatRect bounds;
        int winningPos = Config::DISPLAYED_SYMBOL_AMOUNT / 2;
        std::vector<WinningLine> winningLines;

        void initWinningLines();

    public:
        Machine() = delete;

        Machine(const sf::FloatRect &bounds, size_t reelCount);

        void spin(float duration) {
            for (auto &reel: reels) {
                reel.startSpinning();
            }
        }

        void stopSpinning() {
            for (auto &reel: reels) {
                reel.stopSpinning();
            }
        }

        bool isAnySpinning() {
            bool anySpinning = false;
            for (auto &reel: reels) {
                anySpinning |= reel.isSpinning();
            }
            return anySpinning;
        }

        int calculateWin();

        /// Draws border for view bounds.
        void drawMachineBorder(sf::RenderTarget &target);
        /// Draws border around main winning line.
        void drawWinningBorder(sf::RenderTarget &target);

        /// Renders view border, switches target current view, and delegates rendering to ReelView
        void render(sf::RenderTarget &target);

        /// Calls update in each reel
        void update(float deltaTime);

        /// Generates new reels
        void regenerateReels() {
            reels = std::vector<SlotReel>(reels.size());
        }

        void setWinningLines(const std::vector<WinningLine> &winningLines) {
            this->winningLines = winningLines;
        }
        void disableWinState() {
            for (auto& line : winningLines) line.disableWinState();
        }
    };
}

