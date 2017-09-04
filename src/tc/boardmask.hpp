#ifndef BOARDMASK
#define BOARDMASK

#include <stdint.h>

#include "gamedefs.h"
#include "collapsebuffer.hpp"

namespace tc {
    struct BoardMask {
    public:
        typedef int8_t _size_t; // Signed to facilitate pieces clipping left and down
        
    private:
        static uint8_t const STORE_BYTES{2};
        uint8_t data[STORE_BYTES][GameDefs::HEIGHT];
        
        static_assert(STORE_BYTES <= 127, "Game is wider than BoardMask::_size_t");
        static_assert(GameDefs::HEIGHT <= 127, "Game is taller than BoardMask::_size_t");
        static_assert(GameDefs::WIDTH <= (STORE_BYTES * GameDefs::BYTE_BITS), "Game is wider than storage");
        
        bool row_is_empty(_size_t const);

    public:
        BoardMask();
        
        CollapseBuffer collapse();
        bool get(_size_t const, _size_t const) const;
        void set(_size_t const, _size_t const);
    };
}

#endif
