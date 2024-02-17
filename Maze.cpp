#include <SFML/Graphics.hpp>
#include <iostream>
#include "Maze.h"

void Maze::load(std::vector<std::string> tiles){
    for (int i = 0; i<tiles.size(); i++){
        int row = i/19;
        int col = i%19;
        std::string type;
        if(tiles[i] == "#")
            type="wall";
        if(tiles[i] == "*")
            type="step";
        tile.emplace_back(type, col, row);
    }
}
