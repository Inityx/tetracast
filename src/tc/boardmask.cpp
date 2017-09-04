#include "boardmask.hpp"

#include <string.h> // avr-gcc can't into cstring

namespace tc {
    BoardMask::BoardMask() {
        memset(this->data, 0, sizeof(this->data));
    }
    
    bool BoardMask::row_is_empty(BoardMask::_size_t const row) {
        for(BoardMask::_size_t byte{0}; byte<STORE_BYTES; byte++)
            if(this->data[byte][row] != 0)
                return false;

        return true;
    }

    CollapseBuffer BoardMask::collapse() {
        auto collapse_buffer{CollapseBuffer()};

        // write empty row indeces to buffer
        for(BoardMask::_size_t row{0}; row<GameDefs::HEIGHT; row++)
            if(this->row_is_empty(row))
                collapse_buffer.push_back(row);

        // collapse rows
        auto skip_distance{0};
        for(BoardMask::_size_t row{0}; row<(GameDefs::HEIGHT-skip_distance); row++) {
            if(row == collapse_buffer[skip_distance])
                skip_distance++;

            if(skip_distance == 0)
                continue;

            for(BoardMask::_size_t byte{0}; byte<BoardMask::STORE_BYTES; byte++)
                this->data[byte][row] = this->data[byte][row+skip_distance];
        }
        
        return collapse_buffer;
    }
    
    bool BoardMask::get(
        BoardMask::_size_t const row,
        BoardMask::_size_t const column
    ) const {
        // TODO: space above board should always be false

        // TODO: get board pixel
        return false;
    }
    void BoardMask::set(
        BoardMask::_size_t const row,
        BoardMask::_size_t const column
    ) {
        // TODO: set board pixel
    }
}
