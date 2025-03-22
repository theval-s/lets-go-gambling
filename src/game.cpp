//
// Created by val on 3/19/25.
//

#include "game.hpp"
#include <memory>

RectButton Game::createPlayButton(const float &xpos, const float &ypos, const float &w, const float &h) {
    float xPos = Config::DEFAULT_TOTAL_SLOT_WIDTH + 2 * Config::SPACING;
    std::unique_ptr<sf::Shape> icon = std::make_unique<sf::CircleShape>(sf::CircleShape(h / 2, 3));
    icon->setFillColor(Config::BUTTON_PLAY_COLOR);
    icon->setRotation(sf::degrees(90));

    return RectButton(RectButton(std::move(icon), xpos, ypos, w, h));
}

RectButton Game::createStopButton(const float &xpos, const float &ypos, const float &w, const float &h) {
    //TODO: For more customizable UI positions check if h is bigger than w?
    std::unique_ptr<sf::Shape> icon = std::make_unique<sf::RectangleShape>(sf::RectangleShape({
        h / 4 * 3, h / 4 * 3 // Square inside, 75% of the button height
    }));
    icon->setFillColor(Config::BUTTON_STOP_COLOR);
    return RectButton(RectButton(std::move(icon), xpos,
                                 ypos, w, h));
}

void Game::updateScoreText() {
    scoreText.setString("Score: " + std::to_string(score));
}

Game::Game(const unsigned int &windowWidth, const unsigned int &windowHeight)
    : window(sf::VideoMode({windowWidth, windowHeight}), "OGG Test Game")
      , slots(sf::FloatRect(
                  {Config::SPACING, Config::SPACING},
                  {Config::DEFAULT_TOTAL_SLOT_WIDTH, Config::REEL_HEIGHT}), Config::DEFAULT_REEL_AMOUNT)
      , playButton(createPlayButton(Config::DEFAULT_TOTAL_SLOT_WIDTH + 2 * Config::SPACING, Config::SPACING,
                                    Config::BUTTON_WIDTH, Config::BUTTON_HEIGHT))
      , stopButton(createStopButton(Config::DEFAULT_TOTAL_SLOT_WIDTH + 2 * Config::SPACING,
                                    windowHeight - Config::BUTTON_HEIGHT - Config::SPACING, Config::BUTTON_WIDTH,
                                    Config::BUTTON_HEIGHT))
      , scoreText(font) {
    if (windowHeight == 0 || windowWidth == 0) throw std::invalid_argument("Game window size is zero");
    else if (windowHeight < Config::REEL_HEIGHT || windowWidth < Config::DEFAULT_TOTAL_SLOT_WIDTH)
        throw
                std::invalid_argument("Game window size is too small");

    //Loading font
    if (!font.openFromFile("resources/arial.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        exit(EXIT_FAILURE);
    }
    scoreText.setStyle(sf::Text::Regular);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition({Config::DEFAULT_TOTAL_SLOT_WIDTH + 2 * Config::SPACING, windowHeight / 2.f});

    updateScoreText();

    currentState.changeState(std::make_unique<StartState>(this));
}


void Game::run() {
    while (window.isOpen()) {
        float deltaTime = deltaClock.restart().asSeconds();
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            } else if (event->is<sf::Event::MouseButtonPressed>()) {
                currentState.handleInput(slots);
            }
        }

        window.clear(sf::Color::White); //Possible to delegate it to Config::
        currentState.update(deltaTime, slots);
        currentState.render(window, slots);

        window.draw(playButton); //Might be worthwhile to extract into separate method for scalability?
        window.draw(stopButton);
        window.draw(scoreText);
        window.display();
    }
}
