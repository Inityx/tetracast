#ifndef BLOCK
#define BLOCK

#include "gamedefs.h"

#include <stdint.h> // avr-gcc can't into cstdint

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

namespace tc {
    
    struct Block {
    public:
        // Typedefs
        typedef uint8_t _size_t;

        // Constants
        static uint8_t const NUM_SQUARES = 4;

    private:
        // Constants
        static uint8_t const START_POSITION{ (((GameDefs::WIDTH/2)-1)<<GameDefs::NYBBLE_BITS) | GameDefs::HEIGHT };
        static uint8_t const START_ROTATION{0x00};
        static uint16_t const SHAPES[7];
        
        // Members
        uint8_t storage1;
        uint8_t storage2;
        uint8_t coords;
        uint8_t rotation;
        
        // Methods
        uint8_t square(_size_t const i) const {
            return GameDefs::NYBBLE_BITS * (
                ((i & 0x02) ? this->storage2 : this->storage1 ) >> ( 0x01 - (i & 0x01) )
            );
        }

    public:
        // Constructors
        Block() { this->blank(); }
        Block(
            uint16_t const shape,
            uint8_t const start_coords,
            uint8_t const start_rot
        ) {
            this->storage1 = static_cast<uint8_t>(shape >> 8);
            this->storage2 = static_cast<uint8_t>(shape);
            this->coords   = start_coords;
            this->rotation = start_rot;
        }
        
        // Factories
        static Block random(uint8_t const seed) {
            auto const selection{seed % (sizeof SHAPES)};
            return Block(
                SHAPES[selection],
                START_POSITION,
                START_ROTATION
            );
        }
        
        // Accessors
        inline uint8_t x(_size_t const i) const { return (this->square(i) >> 2) & 0x03; }
        inline uint8_t y(_size_t const i) const { return (this->square(i) >> 1) & 0x01; }
        inline uint8_t e(_size_t const i) const { return (this->square(i) >> 0) & 0x01; }
        inline int8_t global_x(_size_t const i) const { // FIXME: may need tweaking
            return this->loc_x() +                                 // block coord
                ( (this->rotation<2) ? int8_t(1) : int8_t(-1) ) *  // plus or minus
                ( (this->rotation%2) ? this->x(i) : this->y(i) );  // square coord
        }
        inline int8_t global_y(_size_t const i) const { // FIXME: may need tweaking
            return this->loc_y() +                                 // block coord
                ( (this->rotation<2) ? int8_t(1) : int8_t(-1) ) *  // plus or minus
                ( (this->rotation%2) ? this->y(i) : this->x(i) );  // square coord
        }
        
        inline bool is_gone() const {
            return !(
                (this->storage1 & 0x11) ||
                (this->storage2 & 0x11)
            );
        }

        inline uint8_t loc_x() const { return (this->coords & 0xF0) >> GameDefs::NYBBLE_BITS; }
        inline uint8_t loc_y() const { return (this->coords & 0x0F); }

        // Mutators
        inline void move_down() { this->move_down(1); }
        inline void move_down(uint8_t const n) {
            if(n == 0)
                return;

            this->coords = (
                static_cast<uint8_t>(this->loc_x() << GameDefs::NYBBLE_BITS) |
                (this->loc_y() - n)
            );
        }
        inline void move_left() {}
        inline void move_right() {}

        inline void blank() {
            this->storage1 = 0;
            this->storage2 = 0;
            this->coords = 0;
            this->rotation = 0;
        }
    };
}

#endif
