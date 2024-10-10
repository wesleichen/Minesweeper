//
// Created by wesle on 4/19/2024.
//

#include "Tile.h"

// Creates a tile at a given position using coordinates.
Tile::Tile(sf::Vector2f _position) {
    Toolbox& toolbox = Toolbox::getInstance();
    position = _position;
    tile_sprite.setPosition(position);
    state = HIDDEN;
    tile_sprite.setTexture(toolbox.tile_hidden);
}

// Returns the position (coordinates).
sf::Vector2f Tile::getLocation() {
    return position;
}

// Returns the state of the tile.
Tile::State Tile::getState() {
    return state;
}

// Returns the neighbor array containing tile pointers of the tile.
std::array<Tile *, 8> &Tile::getNeighbors() {
    return neighbors;
}

// Sets the state of the tile while ensuring that the
// consequences of each state is executed.
void Tile::setState(Tile::State _state) {
    Toolbox& toolbox = Toolbox::getInstance();
    state = _state;
    if (state == REVEALED) {
        tile_sprite.setTexture(toolbox.tile_revealed);
    } else if (state == HIDDEN) {
        tile_sprite.setTexture(toolbox.tile_hidden);
    } else if (state == FLAGGED) {
        tile_sprite.setTexture(toolbox.tile_hidden);
        flag_sprite.setPosition(position);
        flag_sprite.setTexture(toolbox.flag);
    } else {
        mine_sprite.setPosition(position);
        mine_sprite.setTexture(toolbox.mine);
    }
}

// Sets the neighbor array consisting of tile pointers of a tile.
void Tile::setNeighbors(std::array<Tile *, 8> _neighbors) {
    neighbors = _neighbors;
}

// Details what happens when a tile is left clicked.
void Tile::onClickLeft() {
    Toolbox& toolbox = Toolbox::getInstance();
    // If exploded you lose.
    if (state == EXPLODED) {
        toolbox.newGameButton->getSprite()->setTexture(toolbox.face_lose);
        toolbox.gameState->setPlayStatus(GameState::LOSS);
    } else if (state == HIDDEN) { // If hidden check whether it is a mine or not.
        this->setState(REVEALED);
        int row = position.y/32;
        int column = position.x/32;
        if (toolbox.mines[row][column]) {
            this->setState(EXPLODED);
            toolbox.newGameButton->getSprite()->setTexture(toolbox.face_lose);
            toolbox.gameState->setPlayStatus(GameState::LOSS);
        } else { // Determine to trigger cascading reveal based on adjacent mines.
            int number = toolbox.number[row][column];
            toolbox.pre_debug_flagged[row][column] = true;
            number_sprite.setPosition(position);
            if (number == 0) {
                this->revealNeighbors();
            } else if (number == 1) { // set sprite to appropriate number
                number_sprite.setTexture(toolbox.number_1);
            } else if (number == 2) {
                number_sprite.setTexture(toolbox.number_2);
            } else if (number == 3) {
                number_sprite.setTexture(toolbox.number_3);
            } else if (number == 4) {
                number_sprite.setTexture(toolbox.number_4);
            } else if (number == 5) {
                number_sprite.setTexture(toolbox.number_5);
            } else if (number == 6) {
                number_sprite.setTexture(toolbox.number_6);
            } else if (number == 7) {
                number_sprite.setTexture(toolbox.number_7);
            } else if (number == 8) {
                number_sprite.setTexture(toolbox.number_8);
            }
        }
    }
}

// If a tile is right clicked.
void Tile::onClickRight()
{
    Toolbox &toolbox = Toolbox::getInstance();
    int row = position.y / 32;
    int column = position.x / 32;
    if (state == HIDDEN) // Flags if it was hidden.
    {
        this->setState(FLAGGED);
        toolbox.flag_count += 1;
        toolbox.pre_debug_flagged[row][column] = true;
    } else if (state == FLAGGED){ // Unflags and may reveal a mine if in debug mode.
        this->setState(HIDDEN);
        if (toolbox.debug_status && toolbox.mines[row][column]) {
            this->setState(EXPLODED);
        }
        toolbox.flag_count -= 1;
        toolbox.pre_debug_flagged[row][column] = false;
    } else if (toolbox.debug_status) { // If in debug, can remove already placed
        // flags underneath mines. If no flag, then it places it over the mine.
        if (!toolbox.pre_debug_flagged[row][column]) {
            toolbox.flag_count += 1;
            toolbox.pre_debug_flagged[row][column] = true;
            this->setState(FLAGGED);
        } else {
            toolbox.flag_count -= 1;
            toolbox.pre_debug_flagged[row][column] = false;
        }
    }
}

// Draws the tile onto the window with its respective state.
void Tile::draw() {
    Toolbox& toolbox = Toolbox::getInstance();
    toolbox.window.draw(tile_sprite);
    if (state == REVEALED) {
        int row = position.y/32;
        int column = position.x/32;
        if (toolbox.number[row][column] != 0) {
            toolbox.window.draw(number_sprite);
        }
    } else if (state == FLAGGED) {
        toolbox.window.draw(flag_sprite);
    } else if (state == EXPLODED) {
        toolbox.window.draw(mine_sprite);
    }
}

// Activates the left click function of the neighboring tiles if the initial
// tile had 0 neighbors being a mine. Does nothing if the neighboring tile
// is nullptr.
void Tile::revealNeighbors() {
    Toolbox& toolbox = Toolbox::getInstance();
    int row;
    int column;
    for (Tile* neighbor : neighbors) {
        if (neighbor != nullptr) {
            row = (neighbor->getLocation().y)/32;
            column = (neighbor->getLocation().x)/32;
            // only reveal neighbor is not a mine and is still hidden
            if (toolbox.mines[row][column] == false && neighbor->getState() == HIDDEN) {
                neighbor->onClickLeft();
            }
        }
    }
}