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
    struct Game {
    public:
        // Enums
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
        

    private:
        // members
        BoardMask boardmask;
        BlockVector blocks;
        Block piece;
        uint16_t tick_ms;
        
        // Methods
        bool try_sink_piece();
        bool try_place_piece();
        void collapse_lines();
        void new_piece(uint8_t const);
    
    public:
        // Constructors
        Game() { this->tick_ms = INITIAL_TICK_MS; }
        
        State try_tick(uint16_t const, uint8_t const);
        void try_move(Move const);

        // Debug
        BlockVector const& get_blocks() const { return this->blocks; }
        Block const& get_piece() const { return this->piece; }
    };
}

#endif
