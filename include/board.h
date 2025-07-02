#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>

#define BOARD_SIZE 64
#define BOARD_PIECE_INDICES_SIZE 32
#define BOARD_CASTLING_SIZE 4

typedef struct ChessBoard
{
    int tiles[BOARD_SIZE];
    int piece_indices[BOARD_PIECE_INDICES_SIZE];
    int next_piece_index;
    char castling[BOARD_CASTLING_SIZE];
    char active_color;
    int en_passant_target;
    int half_move_clock;
    int full_move_clock;
} ChessBoard;

void create_board(ChessBoard *board);

void copy_board(ChessBoard *original, ChessBoard *copy);

void play_move_indices(ChessBoard *board, int from_index, int to_index);

void play_move_algebraic(ChessBoard *board, const char move[4]);

int algebraic_to_index(const char algebraic[2]);

void check_castling(struct ChessBoard *board, bool *white_king_castle, bool *white_queen_castle, bool *black_king_castle, bool *black_queen_castle);

#endif
