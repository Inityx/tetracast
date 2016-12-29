#ifdef _POSIX_VERSION
    #include <assert.h>
#endif

#include "boardmask.hpp"

namespace tc {
    BoardMask::BoardMask() {
        for(uint8_t byte = 0; byte<STORE_BYTES; byte++)
            for(uint8_t row=0; row<GAME_HEIGHT; row++)
                storage[byte][row] = 0;
    }
    
    uint8_t BoardMask::collapse(int8_t buff[MAX_COLLAPSE]) {
        boardmask_index skip;
        
        // write indeces to buffer
        skip = 0;
        for(boardmask_index row=0; row<GAME_HEIGHT; row++)
            for(boardmask_index byte=0; byte<STORE_BYTES; byte++)
                if(storage[byte][row] == (uint8_t)(GAME_W_BITMASK >> byte)) {
                    buff[skip] = row;
                    skip++;
                }
        
        // fill remaining with -1
        for(; skip<MAX_COLLAPSE; skip++) buff[skip] = -1;
        
        // collapse rows
        skip = 0;
        for(uint8_t row=0; row<(GAME_HEIGHT-skip); row++) {
            if(row == buff[skip]) skip++;

            if(skip == 0) continue;

            for(uint8_t byte=0; byte<STORE_BYTES; byte++)
                storage[byte][row] = storage[byte][row+skip];
        }
        
        // return number of collapsed rows
        return skip;
    }
    
    bool BoardMask::get(boardmask_index row, boardmask_index column) {
        // TODO: space above board should always be false
#ifdef _POSIX_VERSION
        assert(row > 0 && column > 0);
#endif
        return false;
    }
}
