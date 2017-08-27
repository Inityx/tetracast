#include "boardmask.hpp"

#include <array>

using std::array;

namespace tc {
    // FIXME does this inflate executable size vs iteration?
    BoardMask::BoardMask() {
        this->storage.fill({{0}});
    }
    
    uint8_t BoardMask::collapse(array<int8_t, MAX_COLLAPSE> buffer) {
        uint8_t skip;
        
        // write indeces to buffer
        skip = 0;
        for(boardmask_index row=0; row<GAME_HEIGHT; row++)
            for(boardmask_index byte=0; byte<STORE_BYTES; byte++)
                if(this->storage[byte][row] == static_cast<uint8_t>(GAME_W_BITMASK >> byte)) {
                    buffer[skip] = row;
                    skip++;
                }
        
        // fill remaining with -1
        for(; skip<MAX_COLLAPSE; skip++)
            buffer[skip] = -1;
        
        // collapse rows
        skip = 0;
        for(boardmask_index row=0; row<(GAME_HEIGHT-skip); row++) {
            if(row == buffer[skip])
                skip++;

            if(skip == 0)
                continue;

            for(uint8_t byte=0; byte<STORE_BYTES; byte++)
                this->storage[byte][row] = this->storage[byte][row+skip];
        }
        
        // return number of collapsed rows
        return skip;
    }
    
    bool BoardMask::get(boardmask_index row, boardmask_index column) {
        // TODO: space above board should always be false

        // TODO: get board pixel
        return false;
    }
    void BoardMask::set(boardmask_index row, boardmask_index column) {
        // TODO: set board pixel
    }
}
