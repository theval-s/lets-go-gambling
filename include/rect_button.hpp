//
// Created by val on 3/19/25.
//

#pragma once
#include <memory>

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RenderStates.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Graphics/Shape.hpp"

/// @brief Button class for SFML3.
/// Has a base shape, icon shape positioned in the middle of it, draw method, and isInside(sf::Vector2f) method;
class RectButton final : public sf::Drawable, public sf::Transformable {
private:
    //Maybe use optional for Sprite or Shape? Using just pointer to Transformable/Drawable?
    std::unique_ptr<sf::Shape> base;
    std::unique_ptr<sf::Shape> icon;

public:
    /// Creates rectangle shaped button with size {w,h} at pos {x,y}, and puts icon in the middle of it.
    RectButton(std::unique_ptr<sf::Shape> icon, const float &x, const float &y, const float &w, const float &h);

    /// Draws button in target
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    /// Checks whether mouse_pos is inside the button position.
    bool isInside(const sf::Vector2f &mouse_pos) const;
};
