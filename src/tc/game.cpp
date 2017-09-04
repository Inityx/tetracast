#include <stdio.h>

#include "game.hpp"
#include "block.hpp"

namespace tc {
    // Private
    bool Game::try_sink_piece() {
        puts("Try sink piece");

        if (this->piece.is_gone())
            return false;

        // For each square in the piece
        for(Block::_size_t square_i{0}; square_i<Block::NUM_SQUARES; square_i++) {
            printf("Square %d, y is %d\n", square_i, this->piece.global_y(square_i));

            // if is at board bottom
            if (this->piece.global_y(square_i) == 0)
                return false;
            
            // if is blocked on the bottom
            auto const boardmask_below{
                this->boardmask.get(
                    this->piece.global_y(square_i) - 1,
                    this->piece.global_x(square_i)
                )
            };

            if(boardmask_below)
                return false;
        }
        
        this->piece.move_down();
        return true;
    }
    
    bool Game::try_place_piece() {
        // if block cannot be placed, return false
        // else place block, and return true
        return false;
    }

    void Game::new_piece(uint8_t const seed) {
        puts("Game new piece");
        
        this->piece = Block::random(seed);
    }
    
    void Game::collapse_lines() {}

    // Mutators
    Game::State Game::try_tick(uint16_t const elapsed, uint8_t const random_seed) {
        if(elapsed < this->tick_ms)
            return NO_ACTION;
        
        if(this->tick_ms > MINIMUM_TICK)
            this->tick_ms--;
        
        if(this->piece.is_gone()) {
            puts("Piece is gone");
            this->new_piece(random_seed);
            return TICK;
        }
        
        if(this->try_sink_piece()) {
            puts("Sunk piece");
            return TICK;
        }
        
        if(this->try_place_piece()) {
            puts("Placed piece");

            auto const lines{this->boardmask.collapse()};
            if(!lines.empty()) this->blocks.collapse(lines);
            
            this->piece.blank();
            return TICK;
        }
        
        puts("Could not place piece");
        return LOSE;
    }
    
    
    void Game::try_move(Game::Move const move) {
        // try to move piece
        switch(move){
            case MOV_LEFT:
            case MOV_RIGHT:
                break;
                
            case ROT_LEFT:
            case ROT_RIGHT:
                break;
            
            case DROP:
                while(try_sink_piece());
                break;
        }
    }
}
