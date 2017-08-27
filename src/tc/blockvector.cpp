#include "blockvector.hpp"
#include <array>
#include <cassert>

namespace tc {
    using std::array;

    void BlockVector::append(const Block& new_block) {
        assert(this->size <= MAX_BLK);
        *(this->storage.end()) = new_block;
        this->size++;
    }
    
    void BlockVector::collapse(uint8_t line_count, array<int8_t, MAX_COLLAPSE> lines) {
        for(Block& block : *this) {
            for(square_index square_i=0; square_i<BLOCK_SQUARES; square_i++) {
                // TODO: implement piece squashing
                
                // block must move location down the number of lines below it
                uint8_t accum = 0;
                for(uint8_t line_i = 0; line_i < line_count; line_i++)
                    // TODO optimize if lines are guaranteed sorted
                    if(block.loc_y() > lines[line_i])
                        accum++;
                
                block.move_down(accum);
            }
        }
        
        this->shrink();
    }
    
    void BlockVector::shrink() {
        if(this->size == 0)
            return;
        
        Block* start = this->storage.begin();
        Block* last = this->storage.end() - 1;

        // Bring size to last element
        while(last->is_gone()) {
            last--;
            this->size--;
        }
        
        while(start != last) {
            if(start->is_gone()) {
                *start = *last;
                last--;
                this->size--;
                if(start == last) break;
            }
            start++;
        }
    }

    // Operators
    Block& BlockVector::operator[](bvec_index i) { return storage[i]; }

    // Ranged-for interface
    Block* BlockVector::begin() { return this->storage.begin(); }
    Block* BlockVector::end() { return this->storage.begin() + this->size; }
}
