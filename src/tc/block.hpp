#ifndef BLOCK
#define BLOCK

#include "gamedefs.h"

#include <stdint.h>
#include <array>
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

namespace tc {
    typedef uint8_t square_index;
    
    class Block {
    private:
        uint8_t storage1;
        uint8_t storage2;
        uint8_t coords;
        uint8_t rotation;
        
        uint8_t square(square_index const) const;

    public:
        // Constants
        static std::array<uint16_t, 7> const SHAPES;
        static uint8_t const START_POSITION{ (((GAME_WIDTH/2)-1)<<NYBBLE_BITS) | GAME_HEIGHT };
        static uint8_t const START_ROTATION{0x00};
        
        // Constructors
        Block();
        Block(uint16_t const, uint8_t const, uint8_t const);
        
        // Factories
        static Block random(uint8_t const);
        
        // Accessors
        uint8_t x(square_index const) const;
        uint8_t y(square_index const) const;
        uint8_t e(square_index const) const;
        int8_t global_x(square_index const) const;
        int8_t global_y(square_index const) const;
        
        bool is_gone() const;
        
        uint8_t loc_x() const;
        uint8_t loc_y() const;
        
        // Mutators
        void move_down();
        void move_down(uint8_t const);
        void move_left();
        void move_right();

        void blank();
    };
}

#endif
