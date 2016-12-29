#ifndef BOARDMASK
#define BOARDMASK

#include <stdint.h>

#define STORE_BYTES 2

#if GAME_HEIGHT > 256
    #error Game is taller than index
#endif

#if STORE_BYTES > 256
    #error Game is wider than index
#endif

#include "gamedefs.h"
#if GAME_WIDTH > (STORE_BYTES*8)
    #error Game is wider than storage
#endif

namespace tc {
    typedef uint8_t boardmask_index;
    
    class BoardMask {
        uint8_t storage[STORE_BYTES][GAME_HEIGHT];
        
    public:
        BoardMask();
        
        uint8_t collapse(int8_t [MAX_COLLAPSE]);
        bool get(boardmask_index, boardmask_index);
    };
}

#endif
