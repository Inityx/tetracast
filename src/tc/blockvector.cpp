#include "blockvector.hpp"
#include <array>
#include <cassert>

using std::array;

namespace tc {
    void BlockVector::append(Block const& new_block) {
        assert(this->size <= MAX_BLK);
        *(this->storage.end()) = new_block;
        this->size++;
    }
    
    void BlockVector::collapse(
        uint8_t const line_count,
        CollapseBuffer const& lines
    ) {
        for(auto&& block : *this) {
            for(square_index square_i{0}; square_i<BLOCK_SQUARES; square_i++) {
                // TODO: implement piece squashing
                
                // block must move location down the number of lines below it
                auto accum{0};
                for(auto const line : lines)
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
        
        auto head{ this->storage.begin() };
        auto tail{ this->storage.end() - 1 };

        // Bring tail to last element
        while(tail->is_gone()) {
            tail--;
            this->size--;
        }
        
        // Fill holes from tail
        while(head < tail) {
            if(head->is_gone()) {
                *head = *tail;
                tail--;
                this->size--;
            }
            head++;
        }
    }

    // Operators
    Block& BlockVector::operator[](bvec_index const i) { return this->storage[i]; }
    Block const& BlockVector::operator[](bvec_index const i) const { return this->storage[i]; }

    // Ranged-for interface
    BlockVector::Storage::iterator BlockVector::begin() { return this->storage.begin(); }
    BlockVector::Storage::iterator BlockVector::end() { return this->storage.begin() + this->size; }

    BlockVector::Storage::const_iterator BlockVector::begin() const { return this->storage.begin(); }
    BlockVector::Storage::const_iterator BlockVector::end() const { return this->storage.begin() + this->size; }
}
