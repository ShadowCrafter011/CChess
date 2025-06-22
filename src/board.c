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

// Does not validate move use carefully!
void play_move_indices(ChessBoard *board, int from_index, int to_index)
{
    bool remove_to_piece = board->tiles[to_index] != EMPTY;
    int piece = board->tiles[from_index];
    board->tiles[from_index] = EMPTY;
    board->tiles[to_index] = piece;

    // Update piece indices
    for (int i = 0; i < board->next_piece_index; i++)
    {
        if (board->piece_indices[i] == from_index)
        {
            board->piece_indices[i] = to_index;
        }
        else if (board->piece_indices[i] == to_index && remove_to_piece)
        {
            // Put last piece index in place of to_index in piece_indices and indicate the array is shorter by 1
            board->piece_indices[i] = board->piece_indices[board->next_piece_index - 1];
            board->next_piece_index--;
        }
    }
}

void play_move_algebraic(ChessBoard *board, const char move[4])
{
    const char from[2] = { move[0], move[1] };
    const char to[2] = { move[2], move[3] };
    play_move_indices(board, algebraic_to_index(from), algebraic_to_index(to));
}

int algebraic_to_index(const char algebraic[2])
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
