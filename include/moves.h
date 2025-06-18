#ifndef MOVES_H
#define MOVES_H

#include "list.h"
#include "board.h"

typedef struct Move {
    int start_index;
    int end_index;
} Move;

List generate_moves(ChessBoard *board);

#endif
