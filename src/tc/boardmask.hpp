#ifndef BOARDMASK
#define BOARDMASK

#include <stdint.h>
#include <array>

#include "gamedefs.h"

namespace tc {
    typedef int8_t boardmask_index;
    
    class BoardMask {
    private:
        static uint8_t const STORE_BYTES{2};
        std::array<std::array<uint8_t, GAME_HEIGHT>, STORE_BYTES> storage;
        
        static_assert(STORE_BYTES <= 127, "Game is wider than index");
        static_assert(GAME_HEIGHT <= 127, "Game is taller than index");
        static_assert(GAME_WIDTH <= (STORE_BYTES*BYTE_BITS), "Game is wider than storage");

    public:
        BoardMask();
        
        uint8_t collapse(CollapseBuffer&);
        bool get(boardmask_index const, boardmask_index const) const;
        void set(boardmask_index const, boardmask_index const);
    };
}

#endif
