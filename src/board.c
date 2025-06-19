#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "board.h"
#include "piece.h"

void create_board(ChessBoard *board)
{
    memset(board->tiles, 0, sizeof(board->tiles));
    memset(board->piece_indices, -1, sizeof(board->piece_indices));
    memset(board->castling, '-', sizeof(board->castling));

    board->next_piece_index = 0;
    board->active_color = 'b';
    board->en_passant_target = -1;
    board->half_move_clock = 0;
    board->full_move_clock = 0;
}

int algebraic_to_index(const char *algebraic)
{
    char file = *algebraic;
    char rank = algebraic[1];
    return (8 - rank + '0') * 8 + file - 'a';
}

void check_castling(struct ChessBoard *board, bool *white_king_castle, bool *white_queen_castle, bool *black_king_castle, bool *black_queen_castle)
{
    *white_king_castle = false;
    *white_queen_castle = false;
    *black_king_castle = false;
    *black_queen_castle = false;
    for (int i = 0; i < 4; i++)
    {
        switch (board->castling[i])
        {
        case 'K':
            *white_king_castle = true;
            break;
        case 'Q':
            *white_queen_castle = true;
            break;
        case 'k':
            *black_king_castle = true;
            break;
        case 'q':
            *black_queen_castle = true;
            break;
        }
    }
}
