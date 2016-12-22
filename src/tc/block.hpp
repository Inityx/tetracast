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

#define BLOCK_SQUARES 4
typedef uint8_t square_index;

namespace tc {
    class Block {
        uint8_t storage1;
        uint8_t storage2;
        uint8_t coords;
        uint8_t rotation;
        
        inline uint8_t square(square_index);
        
    public:
        static const uint16_t shapes[7];
        
        Block();
        Block(const Block& src);
        Block(uint16_t, uint8_t, uint8_t);
        
        uint8_t x(square_index);
        uint8_t y(square_index);
        uint8_t e(square_index);
        
        void move_left();
        void move_right();
        void move_down();
        
        Block operator=(const Block&);
        
        void remove();
        bool is_gone();
    };
}

#endif
