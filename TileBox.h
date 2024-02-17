#ifndef PARALLEL_PROGRAMMING_TILEBOX_H
#define PARALLEL_PROGRAMMING_TILEBOX_H

#include <SFML/Graphics.hpp>

class TileBox {
    static const int tileSize = 32;
    public:
        int i,j;
        std::string type;
        sf::RectangleShape box;
        TileBox(std::string ty,int i, int j);
        void drawTile(sf::RenderWindow &window);
};


#endif //PARALLEL_PROGRAMMING_TILEBOX_H
