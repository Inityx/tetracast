#include <stdio.h>

#include "game.hpp"
#include "block.hpp"

namespace tc {
    void Game::new_piece(uint8_t seed) {
        puts("Game new piece");
        piece = Block(
            Block::shapes[
                seed % (sizeof Block::shapes)
            ],
            0x4F,
            0x00
        );
    }
    
    Game::State Game::try_tick(uint16_t elapsed, uint8_t random_seed) {
        if(elapsed < tick_ms) return NO_ACTION;
        
        if(tick_ms > MINIMUM_TICK) tick_ms--;
        
        if(piece.is_gone()) {
            puts("Piece is gone");
            new_piece(random_seed);
            return TICK;
        }
        
        if(try_sink_piece()) {
            puts("Sunk piece");
            return TICK;
        }
        
        if(try_place_piece()) {
            puts("Placed piece");
            int8_t lines[MAX_COLLAPSE];
            uint8_t count;
            
            count = boardmask.collapse(lines);
            if(count > 0) blocks.collapse(count, lines);
            
            piece.remove();
            return TICK;
        }
        
        puts("Could not place piece");
        return LOSE;
    }
    
    bool Game::try_sink_piece() {
        puts("Try sink piece");
        for(square_index square_i=0; square_i<BLOCK_SQUARES; square_i++) {
            printf("Square %d, y is %d\n", square_i, piece.global_y(square_i));
            if(
                !piece.is_gone() && (
                    piece.global_y(square_i) == 0 ||
                    boardmask.get(
                        piece.global_y(square_i) - 1,
                        piece.global_x(square_i)
                    )
                )
            )
                return false;
        }
        
        piece.move_down(1);
        return true;
    }
    
    bool Game::try_place_piece() {
        // if block cannot be placed, return false
        // else place block, and return true
        return false;
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
