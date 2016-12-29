#include "block.hpp"

namespace tc {
    const uint16_t Block::shapes[7] = {
       0x159b, // 0b0001'0101'1001'1011, // left L
       0x37b9, // 0b0011'0111'1011'1001, // right L
       0x1579, // 0b0001'0101'0111'1011, // left S
       0x3759, // 0b0011'0111'0101'1001, // right S
       0x1375, // 0b0001'0011'0111'0101, // square
       0x15d7, // 0b0001'0101'1101'0111, // tee
       0x159d  // 0b0001'0101'1001'1101  // line
    };
   
    Block::Block() {
        remove();
    }
    Block::Block(const Block& src) {
        storage1 = src.storage1;
        storage2 = src.storage2;
        coords   = src.coords;
        rotation = src.rotation;
    }
    Block::Block(uint16_t shape, uint8_t start_coords, uint8_t start_rot) {
        storage1 = static_cast<uint8_t>(shape >> 8);
        storage2 = static_cast<uint8_t>(shape);
        coords = start_coords;
        rotation = start_rot;
    }

    void Block::move_down() { coords = (loc_x()<<NYBBLE_BITS) | (loc_y()-1); }
    
    Block Block::operator=(const Block& rhs) {
        storage1 = rhs.storage1;
        storage2 = rhs.storage2;
        coords   = rhs.coords;
        rotation = rhs.rotation;
        return *this;
    }
    
    void Block::remove() {
        storage1 = storage2 = coords = rotation = 0;
    }
}
