#ifndef SFML_AUX
#define SFML_AUX

#include <SFML/Graphics.hpp>

#include "tc/gamedefs.h"
#include "tc/block.hpp"
#include "tc/blockvector.hpp"

void draw_dots(sf::RenderWindow&, const int);
void draw_block(sf::RenderWindow&, const int, const tc::Block&);
void draw_block_vector(sf::RenderWindow&, const int, const tc::BlockVector&);

void draw_dots(sf::RenderWindow& window, const int scale) {
    const auto radius = scale/16;
    
    sf::CircleShape dot(radius);
    dot.setOrigin(radius, radius);
    dot.setFillColor(sf::Color(64, 0, 0));
    
    for(auto i = 1; i<=tc::GameDefs::HEIGHT; i++) {
        for(auto j = 1; j<=tc::GameDefs::WIDTH; j++) {
            dot.setPosition(scale*j-(scale/2), scale*i-(scale/2));
            window.draw(dot);
        }
    }
}

void draw_block(sf::RenderWindow& window, const int scale, const tc::Block& block) {
    for(
        tc::Block::_size_t square_i = 0;
        square_i<tc::Block::NUM_SQUARES;
        square_i++
    ) {
        // TODO
    }
}

void draw_block_vector(sf::RenderWindow& window, const int scale, const tc::BlockVector& blocks) {
    for(const auto& block : blocks)
        draw_block(window, scale, block);
}

#endif
