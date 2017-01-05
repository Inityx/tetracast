#ifndef SFML_AUX
#define SFML_AUX

#include <SFML/Graphics.hpp>

#include "tc/gamedefs.h"
#include "tc/block.hpp"
#include "tc/blockvector.hpp"

void draw_dots(sf::RenderWindow&, int);
void draw_block(sf::RenderWindow&, int, tc::Block&);
void draw_block_vector(sf::RenderWindow&, int, tc::BlockVector&);

void draw_dots(sf::RenderWindow& window, int scale) {
    int radius = scale/16;
    
    sf::CircleShape dot(radius);
    dot.setOrigin(radius, radius);
    dot.setFillColor(sf::Color(64, 0, 0));
    
    for(int i = 1; i<=GAME_HEIGHT; i++) {
        for(int j = 1; j<=GAME_WIDTH; j++) {
            dot.setPosition(scale*j-(scale/2), scale*i-(scale/2));
            window.draw(dot);
        }
    }
}

void draw_block(sf::RenderWindow& window, int scale, tc::Block& block) {
    for(
        tc::square_index square_i = 0;
        square_i<BLOCK_SQUARES;
        square_i++
    ) {
        // TODO
    }
}

void draw_block_vector(sf::RenderWindow& window, int scale, tc::BlockVector& blocks) {
    for(tc::Block& block : blocks)
        draw_block(window, scale, block);
}

#endif
