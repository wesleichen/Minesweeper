//
// Created by wesle on 4/19/2024.
//

#include "Button.h"

// Constructor accepts a position and onClick_Function for a button.
Button::Button(sf::Vector2f _position, std::function<void(void)> _onClick) {
    position = _position;
    onClick_Function = _onClick;
}

sf::Vector2f Button::getPosition() {
    return position;
};

sf::Sprite* Button::getSprite() {
    return sprite;
}

void Button::setSprite(sf::Sprite* _sprite) {
    sprite = _sprite;
}

// If a button is clicked, its onClick_Function is called.
void Button::onClick() {
    onClick_Function();
}