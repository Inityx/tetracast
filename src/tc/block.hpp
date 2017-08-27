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
    private:
        uint8_t storage1;
        uint8_t storage2;
        uint8_t coords;
        uint8_t rotation;
        
        uint8_t square(square_index i);

    public:
        // Constants
        static const uint16_t shapes[7];
        
        // Constructors
        Block();
        Block(const Block& src);
        Block(uint16_t, uint8_t, uint8_t);
        
        // Accessors
        uint8_t x(square_index i);
        uint8_t y(square_index i);
        uint8_t e(square_index i);
        int8_t global_x(square_index i);
        int8_t global_y(square_index i);
        
        bool is_gone();
        
        uint8_t loc_x();
        uint8_t loc_y();
        
        // Mutators
        void move_down();
        void move_down(uint8_t);
        void move_left();
        void move_right();

        void blank();
        
        // Operators
        Block& operator=(const Block&);
    };
}

#endif
