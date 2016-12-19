#ifndef BLOCK
#define BLOCK

#include <stdint.h>

// Block storage bitmap
/*
  +---+-- MSB
  | x |  Square 0
  | x |    X coord (2 bits)
  | y |    Y coord (1 bit)
  | v |    On/off  (1 bit)
  +---+
  | x |  Square 1
  | x |
  | y |
  | v |
  +---+-- LSB
*/

namespace tc {
    class Block {
        uint8_t storage1;
        uint8_t storage2;
        uint8_t coords;
        uint8_t rotation;
        
        inline uint8_t coord(uint8_t);
        
    public:
        static const uint16_t shapes[7];
        
        Block();
        Block(uint16_t, uint8_t, uint8_t);
        
        uint8_t x(uint8_t);
        uint8_t y(uint8_t);
        uint8_t e(uint8_t);

        Block operator=(const Block&);
        
        void remove();
        bool is_gone();
    };
}

#endif
