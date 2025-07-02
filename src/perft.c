#include "perft.h"
#include "moves.h"

int perft(ChessBoard *board, int depth)
{
    List moves;
    generate_moves(board, &moves);

    if (depth == 1)
    {
        return moves.length;
    }

    int move_counter = 0;

    for (int i = 0; i < moves.length; i += 2)
    {
        ChessBoard new_board = *board;
        play_move_indices(&new_board, moves.values[i], moves.values[i + 1]);
        move_counter += perft(&new_board, depth - 1);
    }

    return move_counter;
}
