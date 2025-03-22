//
// Created by val on 3/21/25.
//

#include "slot_view.hpp"

#include <iostream>

#include "slot_symbol.hpp"

namespace SlotMachine {
    void SlotView::loadTextureFromFile(std::string_view path, ESlotSymbolType type) {
        if (auto &texture = symbolTextures[static_cast<int>(type)]; !texture.loadFromFile(path)) {
            throw std::runtime_error("Failed to load texture from file " + std::string(path));
            texture.setSmooth(true);
        }
    }

    void SlotView::render(sf::RenderTarget &target, const std::vector<SlotReel> &reels) {
        sf::Vector2f viewPosition = target.getView().getCenter() - target.getView().getSize() / 2.f;
        for (size_t i = 0; i < reels.size(); i++) {
            auto &reel = reels[i];
            float pos = reel.getPosition();
            float offsetX = i * (Config::REEL_WIDTH)+   viewPosition.x;

            int ind = static_cast<int>(pos);
            float frac = pos - ind;

            for (int s = -1; s <= Config::DISPLAYED_SYMBOL_AMOUNT; s++) {
                int symIndex = (s + ind) % reel.getSymbolCount();
                if (symIndex < 0) symIndex += reel.getSymbolCount();
                float symY = (s - frac) * Config::SYMBOL_SIZE    +viewPosition.y;

                const SlotSymbol &symbol = reel.getSymbol(symIndex);
                sf::Sprite spr(symbolTextures[static_cast<int>(symbol.getType())]);
                spr.setScale({
                    Config::REEL_WIDTH / spr.getTexture().getSize().x,
                    Config::SYMBOL_SIZE / spr.getTexture().getSize().y
                });
                spr.setPosition({offsetX, symY});

                target.draw(spr);
            }
            sf::RectangleShape border({Config::REEL_WIDTH, Config::DISPLAYED_SYMBOL_AMOUNT * Config::SYMBOL_SIZE});
            border.setPosition({offsetX, viewPosition.y});
            border.setFillColor(sf::Color::Transparent);
            border.setOutlineColor(sf::Color::Black);
            border.setOutlineThickness(1.f);
            target.draw(border);
        }
    }

    void SlotView::loadTextures() {
        symbolTextures.resize(static_cast<int>(ESlotSymbolType::TypesCount));
        try {
            loadTextureFromFile("resources/Banana_96x96.png", ESlotSymbolType::Banana);
            loadTextureFromFile("resources/Bell_96x96.png", ESlotSymbolType::Bell);
            loadTextureFromFile("resources/Cherry_96x96.png", ESlotSymbolType::Cherry);
            loadTextureFromFile("resources/Coin_96x96.png", ESlotSymbolType::Coin);
            loadTextureFromFile("resources/Diamond_96x96.png", ESlotSymbolType::Diamond);
            loadTextureFromFile("resources/Seven_96x96.png", ESlotSymbolType::Seven);
            loadTextureFromFile("resources/Star_96x96.png", ESlotSymbolType::Star);
            loadTextureFromFile("resources/Watermelon_96x96.png", ESlotSymbolType::Watermelon);
        } catch (const std::exception &e) {
            std::cerr << e.what() << '\n';
        }
    }
} //SlotMachine
