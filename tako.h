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


const int64 aFile = C64(72340172838076673);
const int64 hFile = C64(9259542123273814144);
const int64 rank8 = C64(255);
const int64 rank4 = C64(1095216660480);
const int64 rank5 = C64(4278190080);
const int64 fileMasks[] = {
    C64(0x101010101010101), C64(0x202020202020202), C64(0x404040404040404), C64(0x808080808080808),
    C64(0x101010101010101), C64(0x202020202020202), C64(0x404040404040404), C64(0x808080808080808)};

#endif
