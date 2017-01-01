#ifndef BOARDMASK
#define BOARDMASK

#include <stdint.h>

#include "gamedefs.h"

#define STORE_BYTES 2

#if GAME_HEIGHT > 127
    #error Game is taller than index
#endif

#if STORE_BYTES > 127
    #error Game is wider than index
#endif

#if GAME_WIDTH > (STORE_BYTES*8)
    #error Game is wider than storage
#endif

namespace tc {
    typedef int8_t boardmask_index;
    
    class BoardMask {
        uint8_t storage[STORE_BYTES][GAME_HEIGHT];
        
    public:
        BoardMask();
        
        uint8_t collapse(int8_t [MAX_COLLAPSE]);
        bool get(boardmask_index, boardmask_index);
        void set(boardmask_index, boardmask_index);
    };
}

#endif
