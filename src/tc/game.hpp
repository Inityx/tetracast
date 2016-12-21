#ifndef GAME
#define GAME

#include <stdint.h>

#include "boardmask.hpp"
#include "blockvector.hpp"
#include "block.hpp"

#include "gamedefs.h"

#define INITIAL_TICK_MS 1000
#define MINIMUM_TICK 100

namespace tc {
    class Game {
        BoardMask boardmask;
        BlockVector blocks;
        Block piece;
        uint32_t tick_ms;
        
        bool try_sink_piece();
        bool try_place_piece();
        void collapse_lines();
        void new_piece(uint8_t);
    
    public:
        enum State {
            NO_ACTION,
            TICK,
            LOSE
        };
        
        enum Move {
            MOV_LEFT,
            MOV_RIGHT,
            ROT_LEFT,
            ROT_RIGHT,
            DROP
        };
        
        Game() { tick_ms = INITIAL_TICK_MS; }
        State try_tick(uint16_t, uint8_t);
        void try_move(Move);
    };
}

#endif
