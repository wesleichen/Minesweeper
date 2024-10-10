//
// Created by wesle on 4/19/2024.
//

#include <iostream>
#include <fstream>
#include "GameState.h"
#include "Tile.h"

/* GameState constructor that takes in board dimensions and number of
mines. The default is <25, 16> and 50 mines. Turns debug mode off if it
is on. Otherwise resets all aspects of the game. */
GameState::GameState(sf::Vector2i _dimensions, int _numberOfMines) {
    Toolbox& toolbox = Toolbox::getInstance();
    toolbox.flag_count = 0;
    toolbox.row_number = _dimensions.y;
    toolbox.column_number = _dimensions.x;

    if (getDebugMode()) {
        toggleDebugMode();
    }

    toolbox.newGameButton->getSprite()->setTexture(toolbox.face_happy);
    int rows = _dimensions.y;
    int columns = _dimensions.x;
    sf::Vector2f position(0.0f, 0.0f);

    // Resets toolbox arrays, creates new tiles at designated positions.
    for (int row = 0; row < 16; row++) {
        for (int column = 0; column < 25; column++) {
            toolbox.mines[row][column] = false;
            toolbox.pre_debug_flagged[row][column] = false;
            toolbox.number[row][column] = 0;
        }
    }

    for (int row = 0; row < rows; row++) {
        position.y = row * 32;
        for (int column = 0; column < columns; column++) {
            position.x = column * 32;
            tiles[row][column] = new Tile(position);
        }
    }

    int rand_row;
    int rand_column;
    toolbox.mine_count = _numberOfMines;
    // Assigns mines at random positions according to _numberOfMines.
    for (int count = 0; count < _numberOfMines;) {
        rand_row = rand() % rows;
        rand_column = rand() % columns;
        if (!toolbox.mines[rand_row][rand_column]) {
            toolbox.mines[rand_row][rand_column] = true;
            count ++;
        }
    }

    // Assigns neighbors to each tile while ensuring that
    // there are no out of bounds errors or unknown nullptr.
    // Also sets the number of adjacent mines a tile has.
    std::array<Tile*, 8> tile_neighbors{};
    int neighbor_count;
    int adjacent_number;
    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
            neighbor_count = 0;
            adjacent_number = 0;
            for (int row_change = -1; row_change <= 1; row_change++) {
                for (int column_change = -1; column_change <= 1; column_change++)
                {
                    if (row_change == 0 && column_change == 0)
                    {
                        continue;
                    }
                    if ((row + row_change) < 0 || (row + row_change) >= rows)
                    {
                        tile_neighbors[neighbor_count] = nullptr;
                    }
                    else if ((column + column_change) < 0 || (column + column_change) >= columns)
                    {
                        tile_neighbors[neighbor_count] = nullptr;
                    }
                    else {
                        if(toolbox.mines[row + row_change][column + column_change]) {
                            adjacent_number += 1;
                        }
                        tile_neighbors[neighbor_count] = tiles[row + row_change][column + column_change];
                    }
                    neighbor_count += 1;
                }
            }
            tiles[row][column]->setNeighbors(tile_neighbors);
            toolbox.number[row][column] = adjacent_number;
        }
    }
}

// Similar for the Constructor above, except this constructor
// reads in a file name and uses it to open a file.
// Rows are read in and 0's are set normal tiles while
// 1's are set to tiles with a mine.
GameState::GameState(const char *filepath) {
    Toolbox& toolbox = Toolbox::getInstance();
    toolbox.flag_count = 0;
    toolbox.row_number = 16;
    toolbox.column_number = 25;

    if (getDebugMode()) {
        toggleDebugMode();
    }

    toolbox.newGameButton->getSprite()->setTexture(toolbox.face_happy);

    std::ifstream file(filepath, std::ios::binary);
    file.read(testBoard, 416);
    file.close();
    int rows = 16;
    int columns = 25;
    sf::Vector2f position(0.0f, 0.0f);

    int number_of_mines = 0;
    for (int row = 0; row < rows; row++) {
        position.y = row * 32;
        for (int column = 0; column < columns; column++) {
            position.x = column * 32;
            tiles[row][column] = new Tile(position);
            toolbox.mines[row][column] = false;
            toolbox.pre_debug_flagged[row][column] = false;
            toolbox.number[row][column] = 0;
            // If the data is equal to 49 (1's ASCII value), then
            // the respective row, column is set to contain a mine.
            if (int(testBoard[26 * row + column]) == 49) {
                toolbox.mines[row][column] = true;
                number_of_mines += 1;
            }
        }
    }
    toolbox.mine_count = number_of_mines;

    std::array<Tile*, 8> tile_neighbors{};
    int neighbor_count;
    int adjacent_number;
    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
            neighbor_count = 0;
            adjacent_number = 0;
            for (int row_change = -1; row_change <= 1; row_change++) {
                for (int column_change = -1; column_change <= 1; column_change++)
                {
                    if (row_change == 0 && column_change == 0)
                    {
                        continue;
                    }
                    if ((row + row_change) < 0 || (row + row_change) >= rows)
                    {
                        tile_neighbors[neighbor_count] = nullptr;
                    }
                    else if ((column + column_change) < 0 || (column + column_change) >= columns)
                    {
                        tile_neighbors[neighbor_count] = nullptr;
                    }
                    else {
                        if(toolbox.mines[row + row_change][column + column_change]) {
                            adjacent_number += 1;
                        }
                        tile_neighbors[neighbor_count] = tiles[row + row_change][column + column_change];
                    }
                    neighbor_count += 1;
                }
            }
            tiles[row][column]->setNeighbors(tile_neighbors);
            toolbox.number[row][column] = adjacent_number;
        }
    }
}

// Returns the number of flags on the board.
int GameState::getFlagCount() {
    Toolbox& toolbox = Toolbox::getInstance();
    return toolbox.flag_count;
}

// Returns the number of mines in the GameState.
int GameState::getMineCount() {
    Toolbox& toolbox = Toolbox::getInstance();
    return toolbox.mine_count;
}

// Returns the tile at a specified location
// using coordinates, not row, column.
Tile *GameState::getTile(int x, int y) {
    int row = y/32;
    int column = x/32;
    if (row >= 16 || column >= 25) {
        return nullptr;
    }
    return tiles[row][column];
}

// Returns PlayStatus.
GameState::PlayStatus GameState::getPlayStatus() {
    return status;
}

// Sets PlayStatus.
void GameState::setPlayStatus(GameState::PlayStatus _status) {
    status = _status;
}

// Destructor to delete all tiles after use.
GameState::~GameState() {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 25; j++) {
            delete tiles[i][j];
        }
    }
}