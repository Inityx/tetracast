#ifndef SFML_AUX
#define SFML_AUX

#include <SFML/Graphics.hpp>

#include "tc/gamedefs.h"
#include "tc/block.hpp"
#include "tc/blockvector.hpp"

void draw_dots(sf::RenderWindow&, int);
void draw_blocks(sf::RenderWindow&, int, tc::Game&);

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

void draw_blocks(sf::RenderWindow& window, int scale, tc::Game& game) {
    for(
        bvec_index block_i = 0;
        block_i<game.get_blocks().get_size();
        block_i++
    ) {
        tc::Block& block = game.get_blocks()[block_i];
        // draw block
        for(
            square_index square_i = 0;
            square_i<BLOCK_SQUARES;
            square_i++
        ) {
            // TODO
        }
    }   
}
#endif
