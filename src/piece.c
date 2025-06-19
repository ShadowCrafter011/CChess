#include "piece.h"

int char_to_chess_piece(const char *piece_char)
{
    switch (*piece_char)
    {
    case 'p':
        return BLACK_PAWN;
    case 'n':
        return BLACK_KNIGHT;
    case 'b':
        return BLACK_BISHOP;
    case 'r':
        return BLACK_ROOK;
    case 'q':
        return BLACK_QUEEN;
    case 'k':
        return BLACK_KING;
    case 'P':
        return WHITE_PAWN;
    case 'N':
        return WHITE_KNIGHT;
    case 'B':
        return WHITE_BISHOP;
    case 'R':
        return WHITE_ROOK;
    case 'Q':
        return WHITE_QUEEN;
    case 'K':
        return WHITE_KING;
    default:
        return -1;
    }
}
