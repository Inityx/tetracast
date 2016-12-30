#include "blockvector.hpp"

namespace tc {
    void BlockVector::append(const Block& new_block) {
        if(size == MAX_BLK) size = 0;
        storage[size] = new_block;
        size++;
    }
    
    void BlockVector::collapse(uint8_t line_count, int8_t lines[MAX_COLLAPSE]) {
        for(bvec_index block_i=0; block_i<MAX_BLK; block_i++) {
            for(square_index square_i=0; square_i<BLOCK_SQUARES; square_i++) {
                Block& block = storage[block_i];
                
                // TODO: implement piece squashing
                
                // block must move location down the number of lines below it
                uint8_t line_i, accum = 0;
                for(uint8_t line_i = 0; line_i < line_count; line_i++)
                    if(block.loc_y() > lines[line_i])
                        accum++;
                
                block.move_down(accum);
            }
        }
        
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
