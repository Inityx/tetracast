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

// Block coords bitmap
/*
  MSB               LSB
  +---------+---------+
  | x x x x | y y y y |
  +---------+---------+
*/

#define BLOCK_SQUARES 4
#define NYBBLE_BITS 4

namespace tc {
    typedef uint8_t square_index;
    
    class Block {
        uint8_t storage1;
        uint8_t storage2;
        uint8_t coords;
        uint8_t rotation;
        
        inline uint8_t square(square_index i) { return ((i&0x02)?storage2:storage1) >> (0x01-(i&0x01))*NYBBLE_BITS; }
        
    public:
        static const uint16_t shapes[7];
        
        Block();
        Block(const Block& src);
        Block(uint16_t, uint8_t, uint8_t);
        
        inline uint8_t x(square_index i) { return (square(i) >> 2) & 0x03; }
        inline uint8_t y(square_index i) { return (square(i) >> 1) & 0x01; }
        inline uint8_t e(square_index i) { return (square(i) >> 0) & 0x01; }
        inline uint8_t global_x(square_index i) { // FIXME: may need tweaking
            return loc_x() +
                ((rotation%2)?x(i):y(i)) *
                ((rotation<2)?1:-1);
        }
        inline uint8_t global_y(square_index i) { // FIXME: may need tweaking
            return loc_y() +
                ((rotation%2)?y(i):x(i)) *
                ((rotation<2)?1:-1);
        }
        
        inline bool is_gone() {
            return !(
                (storage1 & 0x11) ||
                (storage2 & 0x11)
            );
        }
        
        inline uint8_t loc_x() { return (coords&0xF0) >> NYBBLE_BITS; }
        inline uint8_t loc_y() { return coords&0x0F; }
        
        void move_left();
        void move_right();
        void move_down();
        
        Block operator=(const Block&);
        
        void remove();
    };
}

#endif
