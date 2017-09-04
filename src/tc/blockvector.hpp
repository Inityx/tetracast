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
        BlockVector() { this->size = 0; }
    
        
        void append(Block const&);
        void collapse(uint8_t const, CollapseBuffer const&);
        
        // Operators
        Block& operator[](bvec_index const);
        Block const& operator[](bvec_index const) const;

        // Ranged-for interface
        Storage::iterator begin();
        Storage::iterator end();

        Storage::const_iterator begin() const;
        Storage::const_iterator end() const;
    };
}

#endif
