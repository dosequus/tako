#ifndef TAKO_H
#define TAKO_H

typedef unsigned long long int64;
#define C64(constantInt64) constantInt64##ULL
#define BitVal(data, y) ((data >> y) & 1)      /** Return Data.Y value   **/
#define SetBit(data, y) data |= (1ULL << y)    /** Set Data.Y   to 1    **/
#define ClearBit(data, y) data &= ~(1ULL << y) /** Clear Data.Y to 0    **/
#define ToggleBit(data, y) (data ^= BitVal(y)) /** Toggle Data.Y  value  **/
#define Toggle(data) (data = ~data)            /** Toggle Data value     **/

void arrayToBitboard(char (&)[8][8], int64 &, int64 &, int64 &, int64 &,
                     int64 &, int64 &, int64 &, int64 &,
                     int64 &, int64 &, int64 &, int64 &);

int64 whitePawnMoves(int64 &, int64 &, int64 &, int64 &, int64 &, int64 &,
                     int64 &, int64 &, int64 &, int64 &, int64 &, int64 &);

const int64 aFile = C64(72340172838076673);
const int64 hFile = C64(9259542123273814144);
const int64 rank8 = C64(255);
const int64 rank4 = C64(1095216660480);

#endif