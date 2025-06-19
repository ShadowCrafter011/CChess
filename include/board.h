#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>

typedef struct ChessBoard
{
    int tiles[64];
    int piece_indices[32];
    int next_piece_index;
    char castling[4];
    char active_color;
    int en_passant_target;
    int half_move_clock;
    int full_move_clock;
} ChessBoard;

void create_board(struct ChessBoard *board);

int algebraic_to_index(const char *algebraic);

void check_castling(struct ChessBoard *board, bool *white_king_castle, bool *white_queen_castle, bool *black_king_castle, bool *black_queen_castle);

#endif
