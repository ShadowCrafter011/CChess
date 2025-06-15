#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "piece.c"

struct ChessBoard
{
    int *tiles;
    char *castling;
    char active_color;
    int en_passant_target;
    int half_move_clock;
    int full_move_clock;
};

int createBoard(struct ChessBoard *board)
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

int destructBoard(struct ChessBoard *board)
{
    free(board->tiles);
    free(board->castling);
    board->tiles = NULL;
    board->castling = NULL;
    return 0;
}

int algebraicToIndex(char *algebraic, int *index)
{
    char file = *algebraic;
    char rank = algebraic[1];
    *index = (8 - rank + '0') * 8 + file - 'a';
    return 0;
}

int loadFen(struct ChessBoard *board, char *fen)
{
    int index = 0;
    // Position on the board
    int x = 0;
    // Position in the castling string
    int y = 0;
    // File and rank
    char file = '\0', rank = '\0';
    // Halfmove and Fullmove clock
    int halfmove = 0, fullmove = 0;
    for (int i = 0; i < strlen(fen); i++)
    {
        char c = fen[i];

        if (c == ' ') {
            index++;
            continue;
        }

        switch (index)
        {
            case 0:
                if (c == '/') continue;
                // Skip n files if c is a digit or assign a piece
                if (isdigit(c))
                {
                    int skip = c - '0';
                    x += skip;
                }
                else
                {
                    int piece;
                    charToChessPiece(&c, &piece);
                    board->tiles[x++] = piece;
                }
                break;
            case 1:
                board->active_color = c;
                break;
            case 2:
                board->castling[y++] = c;
                break;
            case 3:
                if (file == '\0')
                {
                    file = c;
                }
                else
                {
                    rank = c;
                    int en_passant_index;
                    char en_passant[2] = {file, rank};
                    algebraicToIndex(en_passant, &en_passant_index);
                    board->en_passant_target = en_passant_index;
                }
                break;
            case 4:
                if (!isdigit(c)) continue;
                halfmove *= 10;
                halfmove += c - '0';
                break;
            case 5:
                if (!isdigit(c)) continue;
                fullmove *= 10;
                fullmove += c - '0';
                break;
        }
    }

    board->half_move_clock = halfmove;
    board->full_move_clock = fullmove;

    return 0;
}

int checkCastling(struct ChessBoard *board, bool *white_king_castle, bool *white_queen_castle, bool *black_king_castle, bool *black_queen_castle)
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
