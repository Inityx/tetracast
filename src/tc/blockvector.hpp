#ifndef BLOCKVECTOR
#define BLOCKVECTOR

#include "block.hpp"
#include <stdint.h>

#include "gamedefs.h"
#if MAX_BLK > 65536
    #error Max block count is larger than vector counter max
#endif

namespace tc {
    class BlockVector {
        Block storage[MAX_BLK];
        uint16_t size;

    public:
        BlockVector() {
            size = 0;
        }
        void append(const Block&);
        void collapse();
    };
}

#endif
