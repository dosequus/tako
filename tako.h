#ifndef TAKO_H
#define TAKO_H



using int64 = uint64_t;
#define C64(constantInt64) constantInt64##ULL
#define GetBit(data, y) (((data) >> (y)) & 1)      /** Get Data.Y value   **/
#define SetBit(data, y) (data) |= (1ULL << (y))    /** Set Data.Y   to 1    **/
#define ClearBit(data, y) (data) &= ~(1ULL << (y)) /** Clear Data.Y to 0    **/
#define ToggleBit(data, y) ((data) ^= GetBit((data), (y))) /** Toggle Data.Y  value  **/
#define Toggle(data) ((data) = ~(data))            /** Toggle Data value     **/

struct bitboard_t 
{
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
std::string whiteBishopMoves(bitboard_t);
std::string whiteRookMoves(bitboard_t);
int64 horizontalVerticalMoves(bitboard_t, int);
int64 diagonalMoves(bitboard_t, int);
std::string whiteSlidingMoves(bitboard_t, int64, std::function<int64(bitboard_t, int)>);

// https://stackoverflow.com/questions/6506356/java-implementation-of-long-numberoftrailingzeros
int trailing_zeros(int64 x)
{
    if(x == 0) return 64;
    int64 a = x, b;
    int n = 63;
    b = a << 32; if(b != 0) { n -= 32; a = b; }
    b = a << 16; if(b != 0) { n -= 16; a = b; }
    b = a <<  8; if(b != 0) { n -=  8; a = b; }
    b = a <<  4; if(b != 0) { n -=  4; a = b; }
    b = a <<  2; if(b != 0) { n -=  2; a = b; }
    return (int)(n - ((a << 1) >> 63));
}

// reverses an unsigned long long with masking and shifting
int64 reverseull(int64 v)
{
    v = ((v & 0xffffffff00000000) >> 32) |((v & 0x00000000ffffffff) << 32);
    v = ((v & 0xffff0000ffff0000) >> 16) |((v & 0x0000ffff0000ffff) << 16);
    v = ((v & 0xff00ff00ff00ff00) >> 8) | ((v & 0x00ff00ff00ff00ff) << 8);
    v = ((v & 0xf0f0f0f0f0f0f0f0) >> 4) | ((v & 0x0f0f0f0f0f0f0f0f) << 4);
    v = ((v & 0xcccccccccccccccc) >> 2) | ((v & 0x3333333333333333) << 2);
    v = ((v & 0xaaaaaaaaaaaaaaaa) >> 1) | ((v & 0x5555555555555555) << 1);
    return v;
}

constexpr int64 A_FILE = C64(72340172838076673);
constexpr int64 H_FILE = C64(9259542123273814144);
constexpr int64 RANK8 = C64(255);
constexpr int64 RANK4 = C64(1095216660480);
constexpr int64 RANK5 = C64(4278190080);
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
