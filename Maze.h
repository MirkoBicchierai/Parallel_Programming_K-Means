#ifndef PARALLEL_PROGRAMMING_MAZE_H
#define PARALLEL_PROGRAMMING_MAZE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "TileBox.h"

class Maze {

    public:
        sf::Texture texture;
        std::vector<TileBox> tile;
        void load(std::vector<std::string> tiles);

};


#endif //PARALLEL_PROGRAMMING_MAZE_H
