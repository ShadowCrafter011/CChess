#include <ctype.h>
#include "fen.h"
#include "piece.h"

enum
{
    PIECE_PLACEMENT = 0,
    ACTIVE_COLOR,
    CASTLING_RIGHTS,
    EN_PASSANT_TARGET,
    HALFMOVE_CLOCK,
    FULLMOVE_CLOCK
};

int load_fen(struct ChessBoard *board, const char *fen)
{
    int index = PIECE_PLACEMENT;
    // Position on the board
    int x = 0;
    // Position in the castling string
    int y = 0;
    // File and rank
    char file = '\0', rank = '\0';
    // Halfmove and Fullmove clock
    int halfmove = 0, fullmove = 0;
    for (int i = 0; fen[i] != '\0'; i++)
    {
        char c = fen[i];

        if (c == ' ')
        {
            index++;
            continue;
        }

        switch (index)
        {
        case PIECE_PLACEMENT:
            if (c == '/')
                continue;
            // Skip n files if c is a digit or assign a piece
            if (isdigit(c))
            {
                int skip = c - '0';
                x += skip;
            }
            else
            {
                int piece = char_to_chess_piece(&c);
                board->piece_indices[board->next_piece_index++] = x;
                board->tiles[x++] = piece;
            }
            break;
        case ACTIVE_COLOR:
            board->active_color = c;
            break;
        case CASTLING_RIGHTS:
            board->castling[y++] = c;
            break;
        case EN_PASSANT_TARGET:
            if (file == '\0')
            {
                file = c;
            }
            else
            {
                rank = c;
                char en_passant[2] = {file, rank};
                int en_passant_index = algebraic_to_index(en_passant);
                board->en_passant_target = en_passant_index;
            }
            break;
        case HALFMOVE_CLOCK:
            halfmove *= 10;
            halfmove += c - '0';
            break;
        case FULLMOVE_CLOCK:
            fullmove *= 10;
            fullmove += c - '0';
            break;
        }
    }

    board->half_move_clock = halfmove;
    board->full_move_clock = fullmove;

    return 0;
}

