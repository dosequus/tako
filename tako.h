#ifndef TAKO_H
#define TAKO_H

typedef unsigned long long int64;
#define C64(constantInt64) constantInt64##ULL
#define GetBit(data, y) (((data) >> (y)) & 1)      /** Get Data.Y value   **/
#define SetBit(data, y) (data) |= (1ULL << (y))    /** Set Data.Y   to 1    **/
#define ClearBit(data, y) (data) &= ~(1ULL << (y)) /** Clear Data.Y to 0    **/
#define ToggleBit(data, y) ((data) ^= GetBit((data), (y))) /** Toggle Data.Y  value  **/
#define Toggle(data) ((data) = ~(data))            /** Toggle Data value     **/

struct bitboard_t {
     int64 wP, wN,
          wB, wR,
          wQ, wK,
          bP, bN,
          bB, bR,
          bQ, bK;
};

void arrayToBitboard(char (&)[8][8], bitboard_t &);
void printBitboard(bitboard_t bboard);

std::string whitePawnMoves(bitboard_t, std::string);


const int64 A_FILE = C64(72340172838076673);
const int64 H_FILE = C64(9259542123273814144);
const int64 RANK8 = C64(255);
const int64 RANK4 = C64(1095216660480);
const int64 RANK5 = C64(4278190080);
constexpr int64 RANK_MASK[]{
    C64(0xFF), C64(0xFF00), C64(0xFF0000), C64(0xFF000000), C64(0xFF00000000), 
    C64(0xFF0000000000), C64(0xFF000000000000), C64(0xFF00000000000000)};
constexpr int64 FILE_MASK[]{
    C64(0x101010101010101), C64(0x202020202020202), C64(0x404040404040404), C64(0x808080808080808),
    C64(0x101010101010101), C64(0x202020202020202), C64(0x404040404040404), C64(0x808080808080808)};
constexpr int64 MAJOR_MASK[]{ // major diagonal
    C64(0x1), C64(0x102), C64(0x10204), C64(0x1020408), C64(0x102040810), C64(0x10204081020), (0x1020408102040),
	C64(0x102040810204080), C64(0x204081020408000), C64(0x408102040800000), C64(0x810204080000000),
	C64(0x1020408000000000), C64(0x2040800000000000), C64(0x4080000000000000), C64(0x8000000000000000)};
constexpr int64 MINOR_MASK[]{ // minor diagonal
    C64(0x80), C64(0x8040), C64(0x804020), C64(0x80402010), C64(0x8040201008), C64(0x804020100804), C64(0x80402010080402),
	C64(0x8040201008040201), C64(0x4020100804020100), C64(0x2010080402010000), C64(0x1008040201000000),
	C64(0x804020100000000), C64(0x402010000000000), C64(0x201000000000000), C64(0x100000000000000)
};
#endif
