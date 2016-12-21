#ifndef BOARDMASK
#define BOARDMASK

#include <stdint.h>

#define STORE_BYTES 2

#include "gamedefs.h"
#if GAME_WIDTH > (STORE_BYTES*8)
    #error Game is wider than storage
#endif

namespace tc {
    class BoardMask {
        uint8_t storage[STORE_BYTES][GAME_HEIGHT];
        
    public:
        BoardMask();
        
        uint8_t collapse(int8_t [MAX_COLLAPSE]);
    };
}

#endif
