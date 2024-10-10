//
// Created by wesle on 4/19/2024.
//

#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "Button.h"
#include "minesweeper.h"


class GameState;

class Toolbox
{
private:
    // Necessary constructor and destructor for Toolbox
    // and an instance to be called and modified.
    static Toolbox* instance;
    Toolbox();
    ~Toolbox();
public:
    // Required functions.
    sf::RenderWindow window;
    GameState* gameState;
    Button* debugButton;
    Button* newGameButton;
    Button* testOneButton;
    Button* testTwoButton;
    Button* testThreeButton;

    static Toolbox& getInstance();


    /* Additional information needed for the smooth
    running of the game. */
    sf::Texture mine;
    sf::Texture tile_hidden;
    sf::Texture tile_revealed;
    sf::Texture number_1;
    sf::Texture number_2;
    sf::Texture number_3;
    sf::Texture number_4;
    sf::Texture number_5;
    sf::Texture number_6;
    sf::Texture number_7;
    sf::Texture number_8;
    sf::Texture flag;
    sf::Texture face_happy;
    sf::Texture face_win;
    sf::Texture face_lose;
    sf::Texture digits;
    sf::Texture debug;
    sf::Texture test_1;
    sf::Texture test_2;

    sf::Sprite test_1_sprite;
    sf::Sprite test_2_sprite;
    sf::Sprite debug_sprite;
    sf::Sprite face_sprite;

    bool debug_status = false; // false if debug_mode is off, true if on

    bool mines[16][25]; // false if no mine, true if mine
    bool pre_debug_flagged[16][25]; // false for hidden, true for flagged AND revealed non-mines
    int number[16][25]; // records number of adjacent mines, 0-8
    int flag_count = 0;
    int mine_count = 0; // total mines in GameState
    int row_number;
    int column_number;

    // Functions for testing boards by reading files.
    void test_board_1();
    void test_board_2();
};
