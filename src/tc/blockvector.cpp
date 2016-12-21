#include "blockvector.hpp"

namespace tc {
    void BlockVector::append(const Block& new_block) {
        if(size == MAX_BLK) size = 0;
        storage[size] = new_block;
        size++;
    }
    
    void BlockVector::collapse(uint8_t count, int8_t lines[MAX_COLLAPSE]) {
        shrink();
    }
    
    void BlockVector::shrink() {
        if(size == 0) return;
        
        Block* start = &storage[0];
        Block* end = &storage[size-1];

        while(end->is_gone()) {
            end--;
            size--;
        }
        
        while(start != end) {
            if(start->is_gone()) {
                *start = *end;
                end--;
                size--;
                if(start == end) break;
            }
            start++;
        }
    }
}
