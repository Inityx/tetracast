#include <stdio.h>

#include "game.hpp"

namespace tc {
    void Game::new_piece(uint8_t seed) {
        piece = Block(
            (uint16_t) Block::shapes[
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
            puts("Sunk block");
            return TICK;
        }
        
        if(try_place_piece()) {
            puts("Placed block");
            piece.remove();
            collapse_lines();
            return TICK;
        }
        
        puts("Return lose");
        return LOSE;
    }
    
    bool Game::try_sink_piece() {
        // if piece can't go down, return false
        // else move piece and return true
        return false;
    }
    
    bool Game::try_place_piece() {
        // if block cannot be placed, return false
        // else place block, and return true
        return false;
    }
    
    void Game::collapse_lines() {
        // collapse full lines and shrink vector
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
