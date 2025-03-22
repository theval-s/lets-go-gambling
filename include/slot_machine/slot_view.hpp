//
// Created by val on 3/21/25.
//

#pragma once
#include <vector>

#include "slot_symbol_type.hpp"
#include <SFML/Graphics.hpp>
#include "slot_reel.hpp"


namespace SlotMachine {
    class SlotView {
    private:
        /// Vector of textures for symbols. Loaded with loadTextures()
        std::vector<sf::Texture> symbolTextures;
        //std::shared_ptr<Machine> machine;

        /// Loads all textures.
        void loadTextures();
        /// Tries to load specific texture. Throws exceptions in case texture is not loade.
        void loadTextureFromFile(std::string_view path, ESlotSymbolType type);

    public:
        explicit SlotView() {
            loadTextures();
        }

        /// Renders Config::DISPLAYED_SYMBOLS_AMOUNT out of reels, based on current reel position
        /// @param target window where reels will be rendered
        /// @param reels const ref to reels
        void render(sf::RenderTarget &target, const std::vector<SlotReel> &reels);
    };
}
