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
    
    void BlockVector::collapse(const uint8_t line_count, const array<int8_t, MAX_COLLAPSE>&& lines) {
        for(auto& block : *this) {
            for(square_index square_i=0; square_i<BLOCK_SQUARES; square_i++) {
                // TODO: implement piece squashing
                
                // block must move location down the number of lines below it
                auto accum = 0;
                for(const auto line : lines)
                    // TODO optimize if lines are guaranteed sorted
                    if(block.loc_y() > line)
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
    Block& BlockVector::operator[](const bvec_index i) { return this->storage[i]; }
    const Block& BlockVector::operator[](const bvec_index i) const { return this->storage[i]; }

    // Ranged-for interface
    BlockVector::Storage::iterator BlockVector::begin() { return this->storage.begin(); }
    BlockVector::Storage::iterator BlockVector::end() { return this->storage.begin() + this->size; }

    BlockVector::Storage::const_iterator BlockVector::begin() const { return this->storage.begin(); }
    BlockVector::Storage::const_iterator BlockVector::end() const { return this->storage.begin() + this->size; }
}
