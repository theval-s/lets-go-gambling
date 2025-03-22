//
// Created by val on 3/19/25.
//
#pragma once

#include "SFML/Graphics/Color.hpp"

namespace Config {
    constexpr float SPACING = 50.f;

    constexpr float REEL_WIDTH = 100.f;
    //constexpr float REEL_HEIGHT = 500.f;
    constexpr int DEFAULT_REEL_AMOUNT = 5;
    constexpr float DEFAULT_TOTAL_SLOT_WIDTH = DEFAULT_REEL_AMOUNT * REEL_WIDTH;
    constexpr int DEFAULT_SYMBOL_AMOUNT = 42;
    constexpr int DISPLAYED_SYMBOL_AMOUNT = 5;
    //constexpr float SYMBOL_SIZE = REEL_HEIGHT / DISPLAYED_SYMBOL_AMOUNT;
    constexpr float SYMBOL_SIZE = 100.f;
    constexpr float REEL_HEIGHT = SYMBOL_SIZE*DISPLAYED_SYMBOL_AMOUNT;
    constexpr bool REGENERATE_SLOTS = true;


    constexpr float BUTTON_WIDTH = 100.f;
    constexpr float BUTTON_HEIGHT = 50.f;
    constexpr sf::Color BUTTON_BASE_COLOR = sf::Color::White;
    constexpr sf::Color BUTTON_OUTLINE_COLOR = sf::Color::Black;
    constexpr sf::Color BUTTON_PLAY_COLOR = sf::Color::Green;
    constexpr sf::Color BUTTON_STOP_COLOR = sf::Color::Red;
    constexpr float BUTTON_OUTLINE_THICKNESS = 2.f;

    constexpr int DEFAULT_SCREEN_WIDTH = REEL_WIDTH * DEFAULT_REEL_AMOUNT + 4 * SPACING + BUTTON_WIDTH;
    constexpr int DEFAULT_SCREEN_HEIGHT = REEL_HEIGHT + SPACING * 2.f;

    constexpr float DEFAULT_SPIN_DURATION = 5.f;
    constexpr float MAX_SPIN_SPEED = 10.f; //Symbols per second
    constexpr float MIN_SPIN_SPEED = 5.f;
    constexpr float DEFAULT_SPIN_SPEED = 2.5f;
    constexpr bool RANDOMIZE_SPIN_SPEED = true;

}
