#include <iostream>
#include <string>
#include <stdlib.h>
#include "tako.h"
using std::string;

int main()
{
     int64 wP = C64(0), wN = C64(0),
           wB = C64(0), wR = C64(0),
           wQ = C64(0), wK = C64(0),
           bP = C64(0), bN = C64(0),
           bB = C64(0), bR = C64(0),
           bQ = C64(0), bK = C64(0);

     char stndrdboard[8][8] = {
         {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
         {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
         {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
         {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};

     char board[8][8] = {
         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
         {'K', 'K', 'K', 'K', 'K', 'K', 'K', 'K'},
         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}};

     arrayToBitboard(board, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK);
     std::cout << wK;
     return 0;
}

void arrayToBitboard(char (&board)[8][8], int64 &wP, int64 &wN,
                     int64 &wB, int64 &wR, int64 &wQ, int64 &wK,
                     int64 &bP, int64 &bN, int64 &bB, int64 &bR,
                     int64 &bQ, int64 &bK)
{
     for (int i = 0; i < 64; i++)
     {
          switch (board[i / 8][i % 8])
          {
          case 'p':
               SetBit(bP, i);
               break;
          case 'n':
               SetBit(bN, i);
               break;
          case 'b':
               SetBit(bB, i);
               break;
          case 'r':
               SetBit(bR, i);
               break;
          case 'q':
               SetBit(bQ, i);
               break;
          case 'k':
               SetBit(bK, i);
               break;
          case 'P':
               SetBit(wP, i);
               break;
          case 'N':
               SetBit(wN, i);
               break;
          case 'B':
               SetBit(wB, i);
               break;
          case 'R':
               SetBit(wR, i);
               break;
          case 'Q':
               SetBit(wQ, i);
               break;
          case 'K':
               SetBit(wK, i);
               break;
          default:
               break;
          }
     }
}

string whitePawnMoves(int64 &wP, int64 &wN,
                      int64 &wB, int64 &wR, int64 &wQ, int64 &wK,
                      int64 &bP, int64 &bN, int64 &bB, int64 &bR,
                      int64 &bQ, int64 &bK, string hist)
{
     // https://www.youtube.com/watch?v=YHeV9sfLCro&list=PLQV5mozTHmacMeRzJCW_8K3qw2miYqd0c&index=7
     // More optimizations on search? something like that
     // (gist is you start searching at MSB and stop at LSB)
     int64 white = wP | wN | wB | wR | wQ | wK;
     int64 black = bP | bN | bB | bR | bQ | bK;
     int64 empty = ~white & ~black;

     string list = "";

     int64 captureLeft = (wP >> 9) & black & ~rank8 & ~hFile;
     for (int i = 0; i < 64; i++)
     {
          if (((captureLeft >> i) & 1) == 1)
          {
               list += "" + std::to_string(i / 8 + 1) + std::to_string(i % 8 + 1) + std::to_string(i / 8) + std::to_string(i % 8);
          }
     }

     int64 captureRight = (wP >> 7) & black & ~rank8 & ~aFile;
     for (int i = 0; i < 64; i++)
     {
          if (((captureLeft >> i) & 1) == 1)
          {
               list += "" + std::to_string(i / 8 + 1) + std::to_string(i % 8 - 1) + std::to_string(i / 8) + std::to_string(i % 8);
          }
     }

     int64 moveForwardOne = (wP >> 8) & empty & ~rank8;
     for (int i = 0; i < 64; i++)
     {
          if (((captureLeft >> i) & 1) == 1)
          {
               list += "" + std::to_string(i / 8 + 1) + std::to_string(i % 8) + std::to_string(i / 8) + std::to_string(i % 8);
          }
     }

     int64 moveForwardTwo = (wP >> 16) & empty & (empty >> 8) & rank4;
     for (int i = 0; i < 64; i++)
     {
          if (((captureLeft >> i) & 1) == 1)
          {
               list += "" + std::to_string(i / 8 + 2) + std::to_string(i % 8) + std::to_string(i / 8) + std::to_string(i % 8);
          }
     }

     int64 promoteLeft = (wP >> 9) & black & rank8 & ~hFile;
     for (int i = 0; i < 64; i++)
     {
          if (((captureLeft >> i) & 1) == 1)
          {
               list += "" + std::to_string(i % 8 + 1) + std::to_string(i % 8) + "QP" + std::to_string(i % 8 + 1) + std::to_string(i % 8) + "RP" + std::to_string(i % 8 + 1) + std::to_string(i % 8) + "BP" + std::to_string(i % 8 + 1) + std::to_string(i % 8) + "KP";
          }
     }

     int64 promoteRight = (wP >> 7) & black & rank8 & ~aFile;
     for (int i = 0; i < 64; i++)
     {
          if (((captureLeft >> i) & 1) == 1)
          {
               list += "" + std::to_string(i % 8 - 1) + std::to_string(i % 8) + "QP" + std::to_string(i % 8 - 1) + std::to_string(i % 8) + "RP" + std::to_string(i % 8 - 1) + std::to_string(i % 8) + "BP" + std::to_string(i % 8 - 1) + std::to_string(i % 8) + "KP";
          }
     }

     int64 promoteUp = (wP >> 8) & empty & rank8;
     for (int i = 0; i < 64; i++)
     {
          if (((captureLeft >> i) & 1) == 1)
          {
               list += "" + std::to_string(i % 8) + std::to_string(i % 8) + "QP" + std::to_string(i % 8) + std::to_string(i % 8) + "RP" + std::to_string(i % 8) + std::to_string(i % 8) + "BP" + std::to_string(i % 8) + std::to_string(i % 8) + "KP";
          }
     }

     if (hist.length() >= 4)
     {
          if ((hist.at(hist.length() - 1) == hist.at(hist.length() - 3)) && abs(hist.at(hist.length() - 2) - hist.at(hist.length() - 4) == 2))
          {
               int file = hist.at(hist.length() - 1) - '0';

               int64 enpassLeft = (wP >> 1) & bP & rank5 & ~hFile & fileMasks[file];
               if (enpassLeft != 0)
               {
                    int index = 0;
                    while (enpassLeft >>= 1)
                         ++index;
                    list += "" + std::to_string(index % 8 + 1) + std::to_string(index % 8) + " E";
               }

               int64 enpassRight = (wP << 1) & bP & rank5 & ~aFile & fileMasks[file];
               if (enpassLeft != 0)
               {
                    int index = 0;
                    while (enpassLeft >>= 1)
                         ++index;
                    list += "" + std::to_string(index % 8 - 1) + std::to_string(index % 8) + " E";
               }
          }
     }

     // Format for now is x1, y1, x2, y2 sans comma and space and then for promotions is y1, y2, piece, P
     return list;
}