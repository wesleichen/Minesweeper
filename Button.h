//
// Created by wesle on 4/19/2024.
//

#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <functional>


class Button
{
private:
    // Storing info about a button.
    sf::Vector2f position;
    sf::Sprite* sprite;
    std::function<void(void)> onClick_Function;
public:
    // Required functions.
    Button(sf::Vector2f _position, std::function<void(void)> _onClick);
    sf::Vector2f getPosition();
    sf::Sprite* getSprite();
    void setSprite(sf::Sprite* _sprite);
    void onClick();
};
