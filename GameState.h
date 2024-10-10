//
// Created by wesle on 4/19/2024.
//

#pragma once
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Toolbox.h"

class Tile;

class GameState
{
public:
    // Required enumeration and functions.
    enum PlayStatus
    {
        WIN, LOSS, PLAYING
    };

    GameState(sf::Vector2i _dimensions = sf::Vector2i(25, 16), int _numberOfMines = 50);

    GameState(const char *filepath);

    int getFlagCount();

    int getMineCount();

    Tile *getTile(int x, int y);

    PlayStatus getPlayStatus();

    void setPlayStatus(PlayStatus _status);

    ~GameState();

private:
    // Storing information about the current GameState.
    char testBoard[416];
    PlayStatus status = PLAYING;
    Tile *tiles[16][25];
};