#include "block.hpp"

namespace tc {
    Block::Block(uint16_t shape) {
        storage1 = shape >> 8;
        storage2 = shape;
        coords = 0x4F;
        rotation = 0x00;
    }
    
    bool Block::is_gone() {
        return !(
            (storage1 & 0x11) || 
            (storage2 & 0x11)
        );
    }

    uint8_t Block::coord(uint8_t n) {
        return ((n&0x2)?storage2:storage1) >> (0x1-(n&0x1))*4;
    }
    uint8_t Block::x(uint8_t n) { return (coord(n) >> 2) & 0x03; }
    uint8_t Block::y(uint8_t n) { return (coord(n) >> 1) & 0x01; }
    uint8_t Block::e(uint8_t n) { return (coord(n) >> 0) & 0x01; }

    Block Block::operator=(const Block& rhs) {
        storage1 = rhs.storage1;
        storage2 = rhs.storage2;
        coords = rhs.coords;
        rotation = rhs.rotation;
        return *this;
    }
}
