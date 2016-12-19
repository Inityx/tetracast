#include "block.hpp"

namespace tc {
    const uint16_t Block::shapes[7] = {
       0b0001'0101'1001'1011, // left L
       0b0011'0111'1011'1001, // right L
       0b0001'0101'0111'1011, // left S
       0b0011'0111'0101'1001, // right S
       0b0001'0011'0111'0101, // square
       0b0001'0101'1101'0111, // tee
       0b0001'0101'1001'1101  // line
    };
   
    Block::Block() {
        remove();
    }
    
    Block::Block(uint16_t shape, uint8_t start_coords, uint8_t start_rot) {
        storage1 = shape >> 8;
        storage2 = shape;
        coords = start_coords;
        rotation = start_rot;
    }

    uint8_t Block::coord(uint8_t n) {
        return ((n&0x2)?storage2:storage1) >> (0x1-(n&0x1))*4;
    }
    uint8_t Block::x(uint8_t n) { return (coord(n) >> 2) & 0b0000'0011; }
    uint8_t Block::y(uint8_t n) { return (coord(n) >> 1) & 0b0000'0001; }
    uint8_t Block::e(uint8_t n) { return (coord(n) >> 0) & 0b0000'0001; }

    Block Block::operator=(const Block& rhs) {
        storage1 = rhs.storage1;
        storage2 = rhs.storage2;
        coords = rhs.coords;
        rotation = rhs.rotation;
        return *this;
    }
    
    void Block::remove() {
        storage1 = storage2 = coords = rotation = 0;
    }
    
    bool Block::is_gone() {
        return !(
            (storage1 & 0b0001'0001) ||
            (storage2 & 0b0001'0001)
        );
    }
}
