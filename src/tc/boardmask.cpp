#include "boardmask.hpp"

#include <array>

using std::array;

namespace tc {
    BoardMask::BoardMask() {
        this->storage.fill({{0}});
    }
    
    uint8_t BoardMask::collapse(CollapseBuffer& skip_buffer) {
        // write indeces to buffer
        auto buf_iter{skip_buffer.begin()};
        for(boardmask_index row{0}; row<GAME_HEIGHT; row++)
            for(boardmask_index byte{0}; byte<STORE_BYTES; byte++)
                if(this->storage[byte][row] == static_cast<uint8_t>(GAME_W_BITMASK >> byte)) {
                    *buf_iter = row;
                    buf_iter++;
                }
        
        // fill remaining with -1
        while(buf_iter < skip_buffer.end()) {
            *buf_iter = -1;
            buf_iter++;
        }
        
        // collapse rows
        auto skip{0};
        for(boardmask_index row{0}; row<(GAME_HEIGHT-skip); row++) {
            if(row == skip_buffer[skip])
                skip++;

            if(skip == 0)
                continue;

            for (auto& byte : this->storage)
                byte[row] = byte[row+skip];
        }
        
        // return number of collapsed rows
        return skip;
    }
    
    bool BoardMask::get(boardmask_index const row, boardmask_index const column) const {
        // TODO: space above board should always be false

        // TODO: get board pixel
        return false;
    }
    void BoardMask::set(boardmask_index const row, boardmask_index const column) {
        // TODO: set board pixel
    }
}
