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
        
        uint8_t square(square_index i) const;

    public:
        // Constants
        static const uint16_t shapes[7];
        
        // Constructors
        Block();
        Block(uint16_t, uint8_t, uint8_t);
        
        // Accessors
        uint8_t x(const square_index i) const;
        uint8_t y(const square_index i) const;
        uint8_t e(const square_index i) const;
        int8_t global_x(const square_index i) const;
        int8_t global_y(const square_index i) const;
        
        bool is_gone() const;
        
        uint8_t loc_x() const;
        uint8_t loc_y() const;
        
        // Mutators
        void move_down();
        void move_down(const uint8_t);
        void move_left();
        void move_right();

        void blank();
    };
}

#endif
