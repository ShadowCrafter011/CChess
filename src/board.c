#include <stdlib.h>
#include <stdbool.h>
#include "board.h"
#include "piece.h"

int create_board(ChessBoard *board)
{
    board->tiles = malloc(8 * 8 * sizeof(int));
    board->castling = malloc(4 * sizeof(char));

    for (int i = 0; i < 64; i++)
    {
        board->tiles[i] = 0;
    }

    for (int i = 0; i < 4; i++)
    {
        board->castling[i] = '-';
    }

    board->active_color = 'b';
    board->en_passant_target = -1;
    board->half_move_clock = 0;
    board->full_move_clock = 0;
    return 0;
}

int destruct_board(struct ChessBoard *board)
{
    free(board->tiles);
    free(board->castling);
    board->tiles = NULL;
    board->castling = NULL;
    return 0;
}

int algebraic_to_index(const char *algebraic, int *index)
{
    char file = *algebraic;
    char rank = algebraic[1];
    *index = (8 - rank + '0') * 8 + file - 'a';
    return 0;
}

int check_castling(struct ChessBoard *board, bool *white_king_castle, bool *white_queen_castle, bool *black_king_castle, bool *black_queen_castle)
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
    return 0;
}
