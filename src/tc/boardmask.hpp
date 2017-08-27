#ifndef BOARDMASK
#define BOARDMASK

#include <stdint.h>
#include <array>

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
    private:
        std::array<std::array<uint8_t, GAME_HEIGHT>, STORE_BYTES> storage;
        
    public:
        BoardMask();
        
        uint8_t collapse(std::array<int8_t, MAX_COLLAPSE>&);
        bool get(boardmask_index, boardmask_index) const;
        void set(boardmask_index, boardmask_index);
    };
}

#endif
