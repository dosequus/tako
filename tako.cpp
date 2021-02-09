#include <iostream>
#include <string>
#include <cstdlib>
#include <functional>

#include "tako.h"

using std::string;

int main()
{
     bitboard_t bboard = {C64(0),C64(0),C64(0),C64(0),C64(0),C64(0),
                         C64(0),C64(0),C64(0),C64(0),C64(0),C64(0)};

     char stndrdboard[8][8] = {
         {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
         {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
         {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
         {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};

     char test_board[8][8] = {
         {' ', ' ', ' ', ' ', ' ', ' ', 'k', ' '},
         {' ', ' ', ' ', ' ', ' ', 'R', ' ', ' '},
         {' ', ' ', ' ', ' ', ' ', ' ', 'P', ' '},
         {' ', ' ', ' ', ' ', 'B', 'p', 'r', 'P'},
         {' ', ' ', ' ', 'p', 'n', ' ', ' ', ' '},
         {' ', ' ', ' ', ' ', ' ', 'K', ' ', ' '},
         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}};

     arrayToBitboard(test_board, bboard);
     std::cout << whiteKnightMoves(bboard) << std::endl;
     return 0;
}

void arrayToBitboard(char (&board)[8][8], bitboard_t &bboard)
{
     for (int i = 0; i < 64; i++)
     {
          switch (board[i / 8][i % 8])
          {
          case 'p':
               SetBit(bboard.bP, i);
               break;
          case 'n':
               SetBit(bboard.bN, i);
               break;
          case 'b':
               SetBit(bboard.bB, i);
               break;
          case 'r':
               SetBit(bboard.bR, i);
               break;
          case 'q':
               SetBit(bboard.bQ, i);
               break;
          case 'k':
               SetBit(bboard.bK, i);
               break;
          case 'P':
               SetBit(bboard.wP, i);
               break;
          case 'N':
               SetBit(bboard.wN, i);
               break;
          case 'B':
               SetBit(bboard.wB, i);
               break;
          case 'R':
               SetBit(bboard.wR, i);
               break;
          case 'Q':
               SetBit(bboard.wQ, i);
               break;
          case 'K':
               SetBit(bboard.wK, i);
               break;
          default:
               break;
          }
     }
}

// for debugging
void printBitboard(bitboard_t bboard)
{
     string board[8] = {"        ",
                    "        ",
                    "        ",
                    "        ",
                    "        ",
                    "        ",
                    "        ",
                    "        "};
     for(int i = 0; i < 64; i++){
          if(GetBit(bboard.wP, i)) board[i/8][i%8] = 'P';
          if(GetBit(bboard.wN, i)) board[i/8][i%8] = 'N';
          if(GetBit(bboard.wB, i)) board[i/8][i%8] = 'B';
          if(GetBit(bboard.wR, i)) board[i/8][i%8] = 'R';
          if(GetBit(bboard.wQ, i)) board[i/8][i%8] = 'Q';
          if(GetBit(bboard.wK, i)) board[i/8][i%8] = 'K';

          if(GetBit(bboard.bP, i)) board[i/8][i%8] = 'p';
          if(GetBit(bboard.bN, i)) board[i/8][i%8] = 'n';
          if(GetBit(bboard.bB, i)) board[i/8][i%8] = 'b';
          if(GetBit(bboard.bR, i)) board[i/8][i%8] = 'r';
          if(GetBit(bboard.bQ, i)) board[i/8][i%8] = 'q';
          if(GetBit(bboard.bK, i)) board[i/8][i%8] = 'k';
     }
     for(auto &rank : board)
          std::cout << rank << std::endl;
}

string whitePawnMoves(bitboard_t board, string hist)
{
     // https://www.youtube.com/watch?v=YHeV9sfLCro&list=PLQV5mozTHmacMeRzJCW_8K3qw2miYqd0c&index=7
     // More optimizations on search? something like that
     // (gist is you start searching at MSB and stop at LSB)
     int64 white = board.wP | board.wN | board.wB | board.wR | board.wQ | board.wK;
     int64 black = board.bP | board.bN | board.bB | board.bR | board.bQ | board.bK;
     int64 empty = ~white & ~black;

     string list = "";

     int64 captureLeft = (board.wP >> 9) & black & ~RANK8 & ~H_FILE;
     for (int i = trailing_zeros(captureLeft); i < 64-trailing_zeros(captureLeft); i++)
     {
          if (GetBit(captureLeft, i))
          {
               list += std::to_string(i / 8 + 1) + std::to_string(i % 8 + 1) + std::to_string(i / 8) + std::to_string(i % 8);
          }
     }

     int64 captureRight = (board.wP >> 7) & black & ~RANK8 & ~A_FILE;
     for (int i = trailing_zeros(captureRight); i < 64-trailing_zeros(captureRight); i++)
     {
          if (GetBit(captureRight, i))
          {
               list += std::to_string(i / 8 + 1) + std::to_string(i % 8 - 1) + std::to_string(i / 8) + std::to_string(i % 8);
          }
     }

     int64 moveForwardOne = (board.wP >> 8) & empty & ~RANK8;
     for (int i = trailing_zeros(moveForwardOne); i < 64-trailing_zeros(moveForwardOne); i++)
     {
          if (GetBit(moveForwardOne, i))
          {
               list += std::to_string(i / 8 + 1) + std::to_string(i % 8) + std::to_string(i / 8) + std::to_string(i % 8);
          }
     }

     int64 moveForwardTwo = (board.wP >> 16) & empty & (empty >> 8) & RANK4;
     for (int i = trailing_zeros(moveForwardTwo); i < 64-trailing_zeros(moveForwardTwo); i++)
     {
          if (GetBit(moveForwardTwo, i))
          {
               list += std::to_string(i / 8 + 2) + std::to_string(i % 8) + std::to_string(i / 8) + std::to_string(i % 8);
          }
     }

     int64 promoteLeft = (board.wP >> 9) & black & RANK8 & ~H_FILE;
     for (int i = trailing_zeros(promoteLeft); i < 64-trailing_zeros(promoteLeft); i++)
     {
          if (GetBit(promoteLeft, i))
          {
               list += std::to_string(i % 8 + 1) + std::to_string(i % 8) + "QP" + std::to_string(i % 8 + 1) + std::to_string(i % 8) + "RP" + std::to_string(i % 8 + 1) + std::to_string(i % 8) + "BP" + std::to_string(i % 8 + 1) + std::to_string(i % 8) + "KP";
          }
     }

     int64 promoteRight = (board.wP >> 7) & black & RANK8 & ~A_FILE;
     for (int i = 0; i < 64; i++)
     {
          if (GetBit(promoteRight, i))
          {
               list += std::to_string(i % 8 - 1) + std::to_string(i % 8) + "QP" + std::to_string(i % 8 - 1) + std::to_string(i % 8) + "RP" + std::to_string(i % 8 - 1) + std::to_string(i % 8) + "BP" + std::to_string(i % 8 - 1) + std::to_string(i % 8) + "KP";
          }
     }

     int64 promoteUp = (board.wP >> 8) & empty & RANK8;
     for (int i = trailing_zeros(promoteUp); i < 64-trailing_zeros(promoteUp); i++)
     {
          if (GetBit(promoteUp, i))
          {
               list += std::to_string(i % 8) + std::to_string(i % 8) + "QP" + std::to_string(i % 8) + std::to_string(i % 8) + "RP" + std::to_string(i % 8) + std::to_string(i % 8) + "BP" + std::to_string(i % 8) + std::to_string(i % 8) + "KP";
          }
     }

     if (hist.length() >= 4)
     {
          if (hist[hist.length() - 1] == hist[hist.length() - 3] && abs(hist[hist.length() - 2 ] - hist[hist.length() - 4] == 2))
          {
               int file = hist[hist.length() - 1] - '0';

               int64 enpassLeft = (board.wP >> 1) & board.bP & RANK5 & ~H_FILE & FILE_MASK[file];
               if (enpassLeft != 0)
               {
                    int index = trailing_zeros(enpassLeft);
                    list += std::to_string(index % 8 + 1) + std::to_string(index % 8) + " E";
               }

               int64 enpassRight = (board.wP << 1) & board.bP & RANK5 & ~A_FILE & FILE_MASK[file];
               if (enpassLeft != 0)
               {
                    int index = trailing_zeros(enpassRight);
                    list += std::to_string(index % 8 - 1) + std::to_string(index % 8) + " E";
               }
          }
     }

     // Format for now is x1, y1, x2, y2 sans comma and space and then for promotions is y1, y2, piece, P
     return list;
}

string whiteBishopMoves(bitboard_t board)
{
     return whiteSlidingMoves(board, board.wB, diagonalMoves);
}

string whiteRookMoves(bitboard_t board)
{
     return whiteSlidingMoves(board, board.wR, horizontalVerticalMoves);
}

string whiteQueenMoves(bitboard_t board)
{
     return whiteSlidingMoves(board, board.wQ, diagonalMoves)+whiteSlidingMoves(board, board.wQ, horizontalVerticalMoves);
}

string whiteSlidingMoves(bitboard_t board, int64 pieceboard, std::function<int64(bitboard_t, int)> moveFunction)
{
     string list;
     int64 piece = pieceboard & ~(pieceboard-1);
     while(piece){
          int piece_index = trailing_zeros(piece);
          int64 moves = moveFunction(board, piece_index);
          int64 sq = moves & ~(moves-1);
          while(sq){
               int index = trailing_zeros(sq);
               list.append(std::to_string(piece_index/8));
               list.append(std::to_string(piece_index%8));
               list.append(std::to_string(index/8));
               list.append(std::to_string(index%8));
               
               moves &= ~sq;
               sq = moves & ~(moves-1);
          }
          pieceboard &= ~piece;
          piece = pieceboard & ~(pieceboard-1);
     }
     return list;
}

string whiteKnightMoves(bitboard_t board){
     string list;
     for(int i = 0; i < 64; i++){
          if(GetBit(board.wK, i)){
               int64 moves = knightAttacks(1 << i);
               int64 sq = moves & ~(moves-1);
               while(sq){
                    int index = trailing_zeros(sq);
                    list.append(std::to_string(i/8));
                    list.append(std::to_string(i%8));
                    list.append(std::to_string(index/8));
                    list.append(std::to_string(index%8));
                    
                    moves &= ~sq;
                    sq = moves & ~(moves-1);
               }
          }
     }
     return list;
}

/**
 * returns all possible squares a piece can move to assuming it is capable of such movement.
 * index: the 1-dimensional index of the piece we are interested in.
 */
int64 horizontalVerticalMoves(bitboard_t board, int index)
{

     int64 occupied = (board.wP | board.wN | board.wB | board.wR | board.wQ | board.wK) 
          | (board.bP | board.bN | board.bB | board.bR | board.bQ | board.bK);
     int64 binary_index = 1 << index; // bit vector
     int64 horizontal = (occupied - binary_index<<1) 
          ^ reverseull(reverseull(occupied) - reverseull(binary_index)<<1);
     int64 vertical = ((occupied&FILE_MASK[index%8]) - binary_index<<1) 
          ^ reverseull(reverseull(occupied&FILE_MASK[index%8]) - reverseull(binary_index)<<1);
     return horizontal&RANK_MASK[index/8] | vertical&FILE_MASK[index%8];
}

int64 diagonalMoves(bitboard_t board, int index)
{
     
     int64 occupied = (board.wP | board.wN | board.wB | board.wR | board.wQ | board.wK) 
          | (board.bP | board.bN | board.bB | board.bR | board.bQ | board.bK);
     int64 binary_index = 1 << index; // bit vector
     int64 major = ((occupied&MAJOR_MASK[(index / 8) + (index % 8)]) - (binary_index<<1)) ^ reverseull(reverseull(occupied&MAJOR_MASK[(index / 8) + (index % 8)]) - (reverseull(binary_index)<<1));
     int64 minor = ((occupied&MINOR_MASK[(index/8)+7-(index%8)]) - (binary_index<<1)) ^ reverseull(reverseull(occupied&MINOR_MASK[(index/8)+7-(index%8)]) - (reverseull(binary_index)<<1));
     return (major&MAJOR_MASK[(index/8)+(index%8)]) | (minor&MINOR_MASK[(index/8)+7-(index%8)]);
}