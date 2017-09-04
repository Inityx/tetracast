#ifndef GAMEDEFS
#define GAMEDEFS

#include <array>

#define BYTE_BITS 8
#define NYBBLE_BITS BYTE_BITS/2

#define GAME_WIDTH 10
#define GAME_HEIGHT 16
#define GAME_W_BITMASK 0x03ff

#define MAX_BLK ((GAME_WIDTH*GAME_HEIGHT)/2)
#define MAX_COLLAPSE 4

typedef std::array<int8_t, MAX_COLLAPSE> CollapseBuffer;

#endif
