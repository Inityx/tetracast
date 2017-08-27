#ifndef BLOCKVECTOR
#define BLOCKVECTOR

#include "block.hpp"
#include <array>
#include <stdint.h>

#include "gamedefs.h"
#if MAX_BLK > 65536
    #error Max block count is larger than vector counter max
#endif

typedef uint16_t bvec_index;

namespace tc {
    class BlockVector {
    private:
        std::array<Block, MAX_BLK> storage;
        bvec_index size;
        
        void shrink();

    public:
        BlockVector() { size = 0; }
        
        
        void append(const Block&);
        void collapse(uint8_t, std::array<int8_t, MAX_COLLAPSE>);
        
        // Operators
        Block& operator[](bvec_index);

        // Ranged-for interface
        Block* begin();
        Block* end();
    };
}

#endif
