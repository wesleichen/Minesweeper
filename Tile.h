//
// Created by wesle on 4/19/2024.
//

#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Toolbox.h"
#include <string>


class Tile
{
public:
    // Required Functions
    enum State{REVEALED, HIDDEN, FLAGGED, EXPLODED};
    Tile(sf::Vector2f _position);
    sf::Vector2f getLocation();
    State getState();
    std::array<Tile*, 8>& getNeighbors();
    void setState(State _state);
    void setNeighbors(std::array<Tile*, 8> _neighbors);
    void onClickLeft();
    void onClickRight();
    void draw();
protected:
    // Required Function
    void revealNeighbors();
private:
    /* Various attributes to store info about a tile
    and to redraw tiles after clicks. */
    sf::Vector2f position;
    State state;
    std::array<Tile*, 8> neighbors;

    sf::Sprite tile_sprite;
    sf::Sprite flag_sprite;
    sf::Sprite mine_sprite;
    sf::Sprite number_sprite;
};
