//
// Created by wesle on 4/19/2024.
//
#include <iostream>
#include "minesweeper.h"
#include "Toolbox.h"
#include "GameState.h"

using namespace std;

// Launches a toolbox and new GameState to start the game with render().
int launch() {
    Toolbox& toolbox = Toolbox::getInstance();
    toolbox.gameState = new GameState();
    render();
    return 0;
}

// Restarts the game by making a new GameState.
void restart() {
    Toolbox& toolbox = Toolbox::getInstance();
    toolbox.gameState = new GameState();
}

void render() {
    float count = 0;

    Toolbox& toolbox = Toolbox::getInstance();
    bool restart_request;
    bool win;

    sf::Vector2f mouse_position;
    sf::Vector2f face_position = toolbox.newGameButton->getPosition();
    sf::Vector2f test_1_position = toolbox.testOneButton->getPosition();
    sf::Vector2f test_2_position = toolbox.testTwoButton->getPosition();
    sf::Vector2f debug_position = toolbox.debugButton->getPosition();

    int mine_counter;
    int positive_mine_count;
    int hundreds_digit, tens_digit, ones_digit;
    sf::Sprite hundreds_digit_sprite;
    sf::Sprite tens_digit_sprite;
    sf::Sprite ones_digit_sprite;
    hundreds_digit_sprite.setPosition(0.0f, 512.0f);
    hundreds_digit_sprite.setTexture(toolbox.digits);
    tens_digit_sprite.setPosition(21.0f, 512.0f);
    tens_digit_sprite.setTexture(toolbox.digits);
    ones_digit_sprite.setPosition(42.0f, 512.0f);
    ones_digit_sprite.setTexture(toolbox.digits);

    while(toolbox.window.isOpen()) {
        sf::Event event;
        toolbox.window.clear();

        mine_counter = toolbox.gameState->getMineCount() - toolbox.gameState->getFlagCount();
        if (mine_counter >= 0) {
            hundreds_digit = mine_counter / 100;
            tens_digit = (mine_counter % 100) / 10;
            ones_digit = (mine_counter % 10);
            hundreds_digit_sprite.setTextureRect(sf::IntRect((hundreds_digit * 21), 0, 21, 32));
        } else {
            positive_mine_count = -1 * mine_counter;
            tens_digit = (positive_mine_count % 100) / 10;
            ones_digit = (positive_mine_count % 10);
            hundreds_digit_sprite.setTextureRect(sf::IntRect((210), 0, 21, 32));
        }
        tens_digit_sprite.setTextureRect(sf::IntRect((tens_digit * 21), 0, 21, 32));
        ones_digit_sprite.setTextureRect(sf::IntRect((ones_digit * 21), 0, 21, 32));

        toolbox.window.draw(hundreds_digit_sprite);
        toolbox.window.draw(tens_digit_sprite);
        toolbox.window.draw(ones_digit_sprite);
        toolbox.window.draw(*(toolbox.debugButton->getSprite()));
        toolbox.window.draw(*(toolbox.newGameButton->getSprite()));
        toolbox.window.draw(*(toolbox.testOneButton->getSprite()));
        toolbox.window.draw(*(toolbox.testTwoButton->getSprite()));

        for (int row = 0; row < toolbox.row_number; row++) {
            for (int column = 0; column < toolbox.column_number; column++) {
                toolbox.gameState->getTile(column * 32, row * 32)->draw();
            }
        }

        toolbox.window.display();

        // THIS CODE TO CONDUCT ACTION AND MOUSE CATCHING
        // To lock play if PlayStatus is WIN or LOSS
        if (toolbox.gameState->getPlayStatus() != GameState::PLAYING) {
            restart_request = false;
            // To lock action until a necessary button has been clicked or until forcefully closed.
            while (!restart_request && toolbox.window.isOpen()) {
                while (toolbox.window.pollEvent(event)) {
                    // Closes if the X is clicked.
                    if (event.type == sf::Event::Closed) {
                        toolbox.window.close();
                    }
                    // If mouse is pressed, the relative location is kept.
                    if (event.type == sf::Event::MouseButtonPressed) {
                        mouse_position = static_cast<sf::Vector2f>(sf::Mouse::getPosition(toolbox.window));
                        // If it was a left click, it checks whether any of the necessary buttons were clicked
                        // such that the loop can be exited. If not, no action occurs.
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            if (mouse_position.x > face_position.x && mouse_position.x < (face_position.x + 64)) {
                                if (mouse_position.y > face_position.y && mouse_position.y < (face_position.y + 64)) {
                                    restart_request = true;
                                    toolbox.newGameButton->onClick();
                                }
                            } else if (mouse_position.x > test_1_position.x && mouse_position.x < (test_1_position.x + 64)) {
                                if (mouse_position.y > test_1_position.y && mouse_position.y < (test_1_position.y + 64)) {
                                    restart_request = true;
                                    toolbox.testOneButton->onClick();
                                }
                            } else if (mouse_position.x > test_2_position.x && mouse_position.x < (test_2_position.x + 64)) {
                                if (mouse_position.y > test_2_position.y && mouse_position.y < (test_2_position.y + 64)) {
                                    restart_request = true;
                                    toolbox.testTwoButton->onClick();
                                }
                            }
                        }
                    }
                }
            }
        }

        Tile* tile;

        // Waits for action to be taken if PlayStatus is PLAYING.
        while (toolbox.window.pollEvent(event)) {
            // Force exits if the X is clicked.
            if (event.type == sf::Event::Closed) {
                toolbox.window.close();
            }
            // If the mouse is used, capture its relative location.
            if (event.type == sf::Event::MouseButtonPressed) {
                mouse_position = static_cast<sf::Vector2f>(sf::Mouse::getPosition(toolbox.window));
                // Attempts to see whether a tile was clicked.
                if (toolbox.gameState->getTile(mouse_position.x, mouse_position.y) != nullptr) {
                    // If so, captures the tile and then either left or right click function
                    // based on which click was used from the mouse.
                    tile = toolbox.gameState->getTile(mouse_position.x, mouse_position.y);
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        tile->onClickLeft();
                    } else if (event.mouseButton.button == sf::Mouse::Right) {
                        tile->onClickRight();
                    }
                    // Displayed changes.
                    tile->draw();
                    toolbox.window.display();
                }
                // If not a tile, but still a left click, determines if any buttons were clicked.
                // If so, activates that tiles function.
                else if (event.mouseButton.button == sf::Mouse::Left) {
                    if (mouse_position.x > face_position.x && mouse_position.x < (face_position.x + 64)) {
                        if (mouse_position.y > face_position.y && mouse_position.y < (face_position.y + 64)) {
                            toolbox.newGameButton->onClick();
                        }
                    } else if (mouse_position.x > test_1_position.x && mouse_position.x < (test_1_position.x + 64)) {
                        if (mouse_position.y > test_1_position.y && mouse_position.y < (test_1_position.y + 64)) {
                            toolbox.testOneButton->onClick();
                        }
                    } else if (mouse_position.x > test_2_position.x && mouse_position.x < (test_2_position.x + 64)) {
                        if (mouse_position.y > test_2_position.y && mouse_position.y < (test_2_position.y + 64)) {
                            toolbox.testTwoButton->onClick();
                        }
                    }
                    else if (mouse_position.x > debug_position.x && mouse_position.x < (debug_position.x + 64)) {
                        if (mouse_position.y > debug_position.y && mouse_position.y < (debug_position.y + 64)) {
                            toolbox.debugButton->onClick();
                        }
                    }
                }
            // check if tile, then buttons
            }
            // Checks if the user has won or not by checking if there are any
            // HIDDEN non mine tiles. If not, then the user wins.
            win = true;
            for (int row = 0; row < toolbox.row_number; row++) {
                for (int column = 0; column < toolbox.column_number; column++) {
                    if (!toolbox.mines[row][column]) {
                        if (!toolbox.pre_debug_flagged[row][column]) {
                            win = false;
                            break;
                        }
                    }
                }
            }

            // If win, PlayStatus is set to WIN to lock play, and the winning face is
            // displayed along with flags on all mine locations.
            if (win) {
                toolbox.gameState->setPlayStatus(GameState::WIN);
                toolbox.newGameButton->getSprite()->setTexture(toolbox.face_win);
                for (int row = 0; row < toolbox.row_number; row++) {
                    for (int column = 0; column < toolbox.column_number; column++) {
                        if (toolbox.mines[row][column]) {
                            toolbox.gameState->getTile(column * 32, row * 32)->setState(Tile::FLAGGED);
                        }
                    }
                }
            }
            // if loss, then the losing face is displayed along with the revealed mines.
            else if (toolbox.gameState->getPlayStatus() == GameState::LOSS) {
                toolbox.newGameButton->getSprite()->setTexture(toolbox.face_lose);
                for (int row = 0; row < toolbox.row_number; row++) {
                    for (int column = 0; column < toolbox.column_number; column++) {
                        if (toolbox.mines[row][column]) {
                            toolbox.gameState->getTile(column * 32, row * 32)->setState(Tile::EXPLODED);
                        }
                    }
                }
            }
        }
    }
}

// Toggles debug mode.
void toggleDebugMode() {
    Toolbox& toolbox = Toolbox::getInstance();
    if (!getDebugMode()) { // if off
        for (int row = 0; row < toolbox.row_number; row++) {
            for (int column = 0; column < toolbox.column_number; column++) {
                if(toolbox.mines[row][column]) { // if mine, reveals the mine
                    toolbox.gameState->getTile(column * 32, row * 32)->setState(Tile::EXPLODED);
                }
            }
        }
    } else {
        for (int row = 0; row < toolbox.row_number; row++) {
            for (int column = 0; column < toolbox.column_number; column++) {
                if(toolbox.mines[row][column]) { // if mine, set back either to FLAGGED or HIDDEN
                    // based on the initial state before debug and after any alterations in debug.
                    if (toolbox.pre_debug_flagged[row][column]) {
                        toolbox.gameState->getTile(column * 32, row * 32)->setState(Tile::FLAGGED);
                    } else {
                        toolbox.gameState->getTile(column * 32, row * 32)->setState(Tile::HIDDEN);
                    }
                }
            }
        }
    }
    // Switches the debug status from on->off or off->on.
    toolbox.debug_status = !toolbox.debug_status;
}

// Returns true if debug mode is on, false otherwise.
bool getDebugMode() {
    Toolbox& toolbox = Toolbox::getInstance();
    return toolbox.debug_status;
}

// Starts minesweeper by calling launch().
int main() { return launch(); }