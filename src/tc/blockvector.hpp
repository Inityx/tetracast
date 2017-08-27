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
    public:
        typedef std::array<Block, MAX_BLK> Storage;

    private:
        Storage storage;
        bvec_index size;
        
        void shrink();

    public:
        BlockVector() { size = 0; }
    
        
        void append(const Block&);
        void collapse(uint8_t, const std::array<int8_t, MAX_COLLAPSE>&&);
        
        // Operators
        Block& operator[](const bvec_index);
        const Block& operator[](const bvec_index) const;

        // Ranged-for interface
        Storage::iterator begin();
        Storage::iterator end();

        Storage::const_iterator begin() const;
        Storage::const_iterator end() const;
    };
}

#endif
