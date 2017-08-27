#include <stdio.h>

#include "game.hpp"
#include "block.hpp"

namespace tc {
    // Private
    bool Game::try_sink_piece() {
        puts("Try sink piece");

        if (this->piece.is_gone())
            return false;

        for(square_index square_i=0; square_i<BLOCK_SQUARES; square_i++) {
            printf("Square %d, y is %d\n", square_i, this->piece.global_y(square_i));

            if (this->piece.global_y(square_i) == 0)
                return false;

            bool boardmask_below = this->boardmask.get(
                this->piece.global_y(square_i) - 1,
                this->piece.global_x(square_i)
            );

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

    void Game::new_piece(uint8_t seed) {
        puts("Game new piece");
        this->piece = Block(
            Block::shapes[
                seed % (sizeof Block::shapes)
            ],
            0x4F,
            0x00
        );
    }
    
    void Game::collapse_lines() {}

    // Mutators
    Game::State Game::try_tick(uint16_t elapsed, uint8_t random_seed) {
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
            std::array<int8_t, MAX_COLLAPSE> lines;
            
            uint8_t count = this->boardmask.collapse(lines);
            if(count > 0) this->blocks.collapse(count, lines);
            
            this->piece.blank();
            return TICK;
        }
        
        puts("Could not place piece");
        return LOSE;
    }
    
    
    void Game::try_move(Game::Move move) {
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
