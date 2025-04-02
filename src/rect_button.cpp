//
// Created by val on 3/19/25.
//

#include "rect_button.hpp"

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RenderStates.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Shape.hpp"
#include "config_values.hpp"

RectButton::RectButton(std::unique_ptr<sf::Shape> icon, float x, float y, float w,
                       float h) : icon(std::move(icon)) {
    base = std::make_unique<sf::RectangleShape>(sf::RectangleShape({w, h}));
    base->setPosition({x, y});
    base->setOutlineColor(Config::BUTTON_OUTLINE_COLOR);
    base->setOutlineThickness(Config::BUTTON_OUTLINE_THICKNESS);

    sf::FloatRect bounds = this->icon->getLocalBounds();
    this->icon->setOrigin({
        bounds.position.x + bounds.size.x / 2.f, bounds.position.y + bounds.size.y / 2.f
    });
    this->icon->setPosition({x + w / 2.f, y + h / 2.f});
}

void RectButton::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(*base, states);
    target.draw(*icon, states);
}

bool RectButton::isInside(const sf::Vector2f &mouse_pos) const {
    if (base->getGlobalBounds().contains(mouse_pos)) return true;
    else return false;
}
