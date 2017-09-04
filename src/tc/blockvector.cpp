#include "gamedefs.h"
#include "blockvector.hpp"
#include "block.hpp"
#include "collapsebuffer.hpp"

namespace tc {
    void BlockVector::collapse(CollapseBuffer const& lines) {
        for(auto&& block : *this) {
            for(Block::_size_t square_i{0}; square_i<Block::NUM_SQUARES; square_i++) {
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
        if(this->num_elements == 0)
            return;
        
        auto head{ this->begin() };
        auto tail{ this->end() - 1 };

        // Bring tail to last element
        while(tail->is_gone()) {
            tail--;
            this->num_elements--;
        }
        
        // Fill holes from tail
        while(head < tail) {
            if(head->is_gone()) {
                *head = *tail;
                tail--;
                this->num_elements--;
            }
            head++;
        }
    }
}
