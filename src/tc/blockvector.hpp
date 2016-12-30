#ifndef BLOCKVECTOR
#define BLOCKVECTOR

#include "block.hpp"
#include <stdint.h>

#include "gamedefs.h"
#if MAX_BLK > 65536
    #error Max block count is larger than vector counter max
#endif

typedef uint16_t bvec_index;

namespace tc {
    class BlockVector {
        Block storage[MAX_BLK];
        bvec_index size;
        
        void shrink();

    public:
        BlockVector() { size = 0; }
        
        Block& operator[](bvec_index index) { return storage[index]; }
        inline bvec_index get_size() { return size; }
        
        void append(const Block&);
        void collapse(uint8_t, int8_t [MAX_COLLAPSE]);
    };
}

#endif
