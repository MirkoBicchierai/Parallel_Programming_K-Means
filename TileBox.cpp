#include "TileBox.h"
#include <iostream>

TileBox::TileBox(std::string ty,int i, int j) {
    type=std::move(ty);
    this->i=i;
    this->j=j;
    box.setPosition((float)(i*tileSize), (float)(j*tileSize));
    box.setSize(sf::Vector2f((float)tileSize,(float)tileSize));
    if(type=="wall")
        box.setFillColor(sf::Color::Red);
    if(type=="step")
        box.setFillColor(sf::Color::White);
}

void TileBox::drawTile(sf::RenderWindow &window) {
    window.draw(box);
}
