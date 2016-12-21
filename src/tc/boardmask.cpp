#include "boardmask.hpp"

#if GAME_HEIGHT > 256
    #error Game is taller than iterator
#endif

namespace tc {
    BoardMask::BoardMask() {
        for(uint8_t byte = 0; byte<STORE_BYTES; byte++)
            for(uint8_t row=0; row<GAME_HEIGHT; row++)
                storage[byte][row] = 0;
    }
    
    uint8_t BoardMask::collapse(int8_t buff[MAX_COLLAPSE]) {
        uint8_t skip;
        
        // write indeces to buffer
        skip = 0;
        for(uint8_t row=0; row<GAME_HEIGHT; row++)
            for(uint8_t byte=0; byte<STORE_BYTES; byte++)
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
}
