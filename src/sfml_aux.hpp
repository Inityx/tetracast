#ifndef SFML_AUX
#define SFML_AUX

#include <SFML/Graphics.hpp>

#include "tc/gamedefs.h"
#include "tc/block.hpp"
#include "tc/blockvector.hpp"

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
    for(bvec_index index = 0; index<game.get_blocks().get_size(); index++) {
        tc::Block& block = game.get_blocks()[index];
    }   
}
#endif
