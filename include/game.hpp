//
// Created by val on 3/19/25.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "state_machine.hpp"
#include "config_values.hpp"
#include "rect_button.hpp"



class Game {
private:

    sf::RenderWindow window;
    StateMachine currentState;
    SlotMachine::Machine slots;

    /// @brief Button that starts slots
    RectButton playButton;
    /// @brief Button that stops slots
    RectButton stopButton;
    /// @brief Text that displays current score
    sf::Text scoreText;
    /// @brief Font for scoreText
    sf::Font font;

    int score = 0;
    sf::Clock deltaClock;

    /// @brief creates a button with a green triangle inside
    /// @param xpos x position of a resulting button
    /// @param ypos y position of a resulting button
    /// @param w width of a resulting button
    /// @param h height of a resulting button
    /// @return created button
    static RectButton createPlayButton(const float &xpos, const float &ypos, const float &w, const float &h);

    /// @brief creates a button with a green triangle inside
    /// @param xpos x position of a resulting button
    /// @param ypos y position of a resulting button
    /// @param w width of a resulting button
    /// @param h height of a resulting button
    /// @return created button
    static RectButton createStopButton(const float &xpos, const float &ypos, const float &w, const float &h);
    void updateScoreText();

public:

    /// Default constructor tries to create window with size enough to contain buttons and slots and delegates construction
    Game()
        : Game(
            Config::DEFAULT_TOTAL_SLOT_WIDTH + Config::SPACING * 3 + Config::BUTTON_WIDTH,
            Config::REEL_HEIGHT+Config::SPACING*2) {
    };


    Game(const unsigned int &windowWidth, const unsigned int &windowHeight);

    /// Calls StateMachine's changeState
    void changeState(std::unique_ptr<IState> newState) {
        currentState.changeState(std::move(newState));
    }

    /// Main game loop
    void run();

    int getScore() const { return score; }
    void addScore(const int &amount) {
        score += amount;
        updateScoreText();
    }

    /// Game handles the input so this function is called by the states when needed
    bool isPlayButtonClicked() const {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        return playButton.isInside(mousePos);
    }

    /// Game handles the input so this function is called by the states when needed
    bool isStopButtonClicked() const {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        return stopButton.isInside(mousePos);
    }
};
