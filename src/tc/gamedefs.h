#ifndef GAMEDEFS
#define GAMEDEFS

#include <stdint.h> // avr-gcc can't into cstdint

namespace tc {
    struct GameDefs {
    public:
        static uint8_t const WIDTH{10};
        static uint8_t const HEIGHT{16};
        static uint8_t const MAX_COLLAPSE{4};

        static uint8_t const BYTE_BITS{8};
        static uint8_t const NYBBLE_BITS{BYTE_BITS/2};
    };
}
#endif
