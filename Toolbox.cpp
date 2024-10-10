//
// Created by wesle on 4/19/2024.
//

#include "Toolbox.h"
#include "GameState.h"
using namespace std;

// Assigns instance to nullptr to be set.
Toolbox* Toolbox::instance = nullptr;

// Both test functions create a new GameState with the give file name.
void Toolbox::test_board_1() {
    const char* filename = "boards/testboard1.brd";
    gameState = new GameState(filename);
}

void Toolbox::test_board_2() {
    const char* filename = "boards/testboard2.brd";
    gameState = new GameState(filename);
}

// Creates the window and loads all necessary elements needed for the game to run.
Toolbox::Toolbox() {
    window.create(sf::VideoMode(800, 600), "P4 - Minesweeper, <Wesley Chen>");

    mine.loadFromFile("images/mine.png");
    tile_hidden.loadFromFile("images/tile_hidden.png");
    tile_revealed.loadFromFile("images/tile_revealed.png");
    number_1.loadFromFile("images/number_1.png");
    number_2.loadFromFile("images/number_2.png");
    number_3.loadFromFile("images/number_3.png");
    number_4.loadFromFile("images/number_4.png");
    number_5.loadFromFile("images/number_5.png");
    number_6.loadFromFile("images/number_6.png");
    number_7.loadFromFile("images/number_7.png");
    number_8.loadFromFile("images/number_8.png");
    flag.loadFromFile("images/flag.png");
    face_happy.loadFromFile("images/face_happy.png");
    face_win.loadFromFile("images/face_win.png");
    face_lose.loadFromFile("images/face_lose.png");
    digits.loadFromFile("images/digits.png");
    debug.loadFromFile("images/debug.png");
    test_1.loadFromFile("images/test_1.png");
    test_2.loadFromFile("images/test_2.png");

    // Creates all the buttons along with their respective functions.
    std::function<void(void)> test_1_function = [this](){test_board_1();};
    sf::Vector2f t1_sprite_position(560.0f, 512.0f);
    test_1_sprite.setPosition(t1_sprite_position.x, t1_sprite_position.y);
    test_1_sprite.setTexture(test_1);
    testOneButton = new Button(t1_sprite_position, test_1_function);
    testOneButton->setSprite(&test_1_sprite);

    std::function<void(void)> test_2_function = [this](){test_board_2();};
    sf::Vector2f t2_sprite_position(624.0f, 512.0f);
    test_2_sprite.setPosition(t2_sprite_position.x, t2_sprite_position.y);
    test_2_sprite.setTexture(test_2);
    testTwoButton = new Button(t2_sprite_position, test_2_function);
    testTwoButton->setSprite(&test_2_sprite);

    std::function<void(void)> debug_function = [](){toggleDebugMode();};
    sf::Vector2f debug_sprite_position(496.0f, 512.0f);
    debug_sprite.setPosition(debug_sprite_position.x, debug_sprite_position.y);
    debug_sprite.setTexture(debug);
    debugButton = new Button(debug_sprite_position, debug_function);
    debugButton->setSprite(&debug_sprite);

    std::function<void(void)> face_function = [](){restart();};
    sf::Vector2f face_sprite_position(368.0f, 512.0f);
    face_sprite.setPosition(face_sprite_position.x, face_sprite_position.y);
    face_sprite.setTexture(face_happy);
    newGameButton = new Button(face_sprite_position, face_function);
    newGameButton->setSprite(&face_sprite);
}

// If instance has not been called for, returns new Toolbox,
// else, returns current Toolbox. Ensures singleton behavior.
Toolbox& Toolbox::getInstance() {
    if (instance == nullptr) {
        instance = new Toolbox();
    }
    return *instance;
}

// Destructor deletes info that the Toolbox class uses.
Toolbox::~Toolbox() {
    delete debugButton;
    delete newGameButton;
    delete testOneButton;
    delete testTwoButton;
    delete testThreeButton;
    delete gameState;
}