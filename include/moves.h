#ifndef MOVES_H
#define MOVES_H

#include "list.h"
#include "board.h"

typedef struct Move {
    int start_index;
    int end_index;
} Move;

void generate_moves(ChessBoard *board, List *list);

#endif
