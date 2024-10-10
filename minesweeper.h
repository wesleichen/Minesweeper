//
// Created by wesle on 4/19/2024.
//

#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "Tile.h"

class Toolbox;

// Prototyping global functions.
int launch();
void restart();
void render();
void toggleDebugMode();
bool getDebugMode();
