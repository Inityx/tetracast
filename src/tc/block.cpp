#include "block.hpp"

namespace tc {
    uint16_t const Block::SHAPES[7]{
       0x159b, // 0b0001'0101'1001'1011, // left L
       0x37b9, // 0b0011'0111'1011'1001, // right L
       0x1579, // 0b0001'0101'0111'1011, // left S
       0x3759, // 0b0011'0111'0101'1001, // right S
       0x1375, // 0b0001'0011'0111'0101, // square
       0x15d7, // 0b0001'0101'1101'0111, // tee
       0x159d  // 0b0001'0101'1001'1101  // line
    };
}
