#ifndef BLOCK
#define BLOCK

#include <stdint.h>

namespace tc {
    class Block {
        uint8_t storage1;
        uint8_t storage2;
        uint8_t coords;
        uint8_t rotation;
        
        inline uint8_t coord(uint8_t);
        
    public:
        Block() {}
        Block(uint16_t);
        
        uint8_t x(uint8_t);
        uint8_t y(uint8_t);
        uint8_t e(uint8_t);

        Block operator=(const Block&);
        bool is_gone();
    };
}

#endif
