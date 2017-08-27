#include "block.hpp"

namespace tc {
    // Private methods
    uint8_t Block::square(square_index i) {
        return NYBBLE_BITS * (
            ((i & 0x02) ? this->storage2 : this->storage1 ) >> ( 0x01 - (i & 0x01) )
        );
    }

    // Constants
    const uint16_t Block::shapes[7] = {
       0x159b, // 0b0001'0101'1001'1011, // left L
       0x37b9, // 0b0011'0111'1011'1001, // right L
       0x1579, // 0b0001'0101'0111'1011, // left S
       0x3759, // 0b0011'0111'0101'1001, // right S
       0x1375, // 0b0001'0011'0111'0101, // square
       0x15d7, // 0b0001'0101'1101'0111, // tee
       0x159d  // 0b0001'0101'1001'1101  // line
    };

    // Constructors
    Block::Block() { this->blank(); }
    
    Block::Block(const Block& src) {
        this->storage1 = src.storage1;
        this->storage2 = src.storage2;
        this->coords   = src.coords;
        this->rotation = src.rotation;
    }
    
    Block::Block(uint16_t shape, uint8_t start_coords, uint8_t start_rot) {
        this->storage1 = static_cast<uint8_t>(shape >> 8);
        this->storage2 = static_cast<uint8_t>(shape);
        this->coords   = start_coords;
        this->rotation = start_rot;
    }

    // Accessors
    uint8_t Block::x(square_index i) { return (this->square(i) >> 2) & 0x03; }
    uint8_t Block::y(square_index i) { return (this->square(i) >> 1) & 0x01; }
    uint8_t Block::e(square_index i) { return (this->square(i) >> 0) & 0x01; }
    int8_t Block::global_x(square_index i) { // FIXME: may need tweaking
        return this->loc_x() +                                 // block coord
            ( (this->rotation<2) ? int8_t(1) : int8_t(-1) ) *  // plus or minus
            ( (this->rotation%2) ? this->x(i) : this->y(i) );  // square coord
    }
    int8_t Block::global_y(square_index i) { // FIXME: may need tweaking
        return this->loc_y() +                                 // block coord
            ( (this->rotation<2) ? int8_t(1) : int8_t(-1) ) *  // plus or minus
            ( (this->rotation%2) ? this->y(i) : this->x(i) );  // square coord
    }
    
    bool Block::is_gone() {
        return !(
            (this->storage1 & 0x11) ||
            (this->storage2 & 0x11)
        );
    }

    uint8_t Block::loc_x() { return (this->coords & 0xF0) >> NYBBLE_BITS; }
    uint8_t Block::loc_y() { return (this->coords & 0x0F); }

    // Mutators
    void Block::move_down() { this->move_down(1); }
    void Block::move_down(uint8_t n) {
        if(n == 0) return;

        this->coords = (
            static_cast<uint8_t>(this->loc_x() << NYBBLE_BITS) |
            (this->loc_y() - n)
        );
    }
    void Block::move_left() {}
    void Block::move_right() {}

    void Block::blank() {
        this->storage1 = 0;
        this->storage2 = 0;
        this->coords = 0;
        this->rotation = 0;
    }
    
    // Operators
    Block& Block::operator=(const Block& rhs) {
        this->storage1 = rhs.storage1;
        this->storage2 = rhs.storage2;
        this->coords   = rhs.coords;
        this->rotation = rhs.rotation;
        return *this;
    }
}
