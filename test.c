#include <stdio.h>
#include <stdbool.h>
#include "minunit.h"
#include "board.c"

int tests_run = 0;

static char *test_fen_1()
{
    struct ChessBoard board;
    createBoard(&board);
    loadFen(&board, "rnb2bnr/ppppkppp/8/4p1q1/P1PP3P/R2Q4/1P2PPP1/1NB1KBNR b K c3 158 1000");

    bool K = false, Q = false, k = false, q = false;
    checkCastling(&board, &K, &Q, &k, &q);
    mu_assert("White cannot king side castle for fen 1", K);
    mu_assert("White can queen side castle for fen 1", !Q);
    mu_assert("Black can king side castle for fen 1", !k);
    mu_assert("Black can queen side castle for fen 1", !q);

    mu_assert("En passant target is not 42 target c3 for fen 1", board.en_passant_target == 42);

    mu_assert("It is not blacks turn to move fen 1", board.active_color == 'b');

    mu_assert("Halfmove clock is not 158 for fen 1", board.half_move_clock == 158);
    mu_assert("Fullmove clock is not 1000 for fen 1", board.full_move_clock == 1000);

    int expected[64] = {
        BLACK_ROOK, BLACK_KNIGHT, BLACK_BISHOP, EMPTY, EMPTY, BLACK_BISHOP, BLACK_KNIGHT, BLACK_ROOK,
        BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_KING, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN,
        EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
        EMPTY, EMPTY, EMPTY, EMPTY, BLACK_PAWN, EMPTY, BLACK_QUEEN, EMPTY,
        WHITE_PAWN, EMPTY, WHITE_PAWN, WHITE_PAWN, EMPTY, EMPTY, EMPTY, WHITE_PAWN,
        WHITE_ROOK, EMPTY, EMPTY, WHITE_QUEEN, EMPTY, EMPTY, EMPTY, EMPTY,
        EMPTY, WHITE_PAWN, EMPTY, EMPTY, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, EMPTY,
        EMPTY, WHITE_KNIGHT, WHITE_BISHOP, EMPTY, WHITE_KING, WHITE_BISHOP, WHITE_KNIGHT, WHITE_ROOK
    };

    for (int i = 0; i < 64; i++)
    {
        mu_assert("Board does not match expected values for fen 1", board.tiles[i] == expected[i]);
    }

    return 0;
}

static char *test_start_fen()
{
    struct ChessBoard board;
    createBoard(&board);
    loadFen(&board, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    mu_assert("It is not whites turn for start fen", board.active_color == 'w');

    bool black_king_side_castle, black_queen_side_castle, white_king_side_castle, white_queen_side_castle;
    checkCastling(&board, &white_king_side_castle, &white_queen_side_castle, &black_king_side_castle, &black_queen_side_castle);
    mu_assert("Black cannot castle king side for start fen", black_king_side_castle);
    mu_assert("Black cannot castle queen side for start fen", black_queen_side_castle);
    mu_assert("White cannot castle king side for start fen", white_king_side_castle);
    mu_assert("White cannot castle queen side for start fen", white_queen_side_castle);

    mu_assert("There is an en passant target square for start fen", board.en_passant_target == -1);

    mu_assert("The halfmove clock is not 0 for start fen", board.half_move_clock == 0);
    mu_assert("The fullmove clock is not 1 for start fen", board.full_move_clock == 1);

    int expected[64] = {
        BLACK_ROOK, BLACK_KNIGHT, BLACK_BISHOP, BLACK_QUEEN, BLACK_KING, BLACK_BISHOP, BLACK_KNIGHT, BLACK_ROOK,
        BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN,
        EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
        EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
        EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
        EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
        WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN,
        WHITE_ROOK, WHITE_KNIGHT, WHITE_BISHOP, WHITE_QUEEN, WHITE_KING, WHITE_BISHOP, WHITE_KNIGHT, WHITE_ROOK
    };

    for (int i = 0; i < 64; i++)
    {
        mu_assert("Board does not match expected values for start fen", board.tiles[i] == expected[i]);
    }

    return 0;
}

static char *test_en_passant_fen()
{
    struct ChessBoard board;
    createBoard(&board);
    loadFen(&board, "8/8/8/8/8/8/8/8 w - a8 0 1");
    mu_assert("En passant target is not index 0 for a8 fen", board.en_passant_target == 0);
    loadFen(&board, "8/8/8/8/8/8/8/8 w - h1 0 1");
    mu_assert("En passant target is not index 63 for h1 fen", board.en_passant_target == 63);
    return 0;
}

static char *test_empty_fen()
{
    struct ChessBoard board;
    createBoard(&board);
    loadFen(&board, "8/8/8/8/8/8/8/8 w - - 0 1");
    for (int i = 0; i < 8 * 8; i++)
    {
        mu_assert("Value in empty chess board loaded by fen is not 0", board.tiles[i] == 0);
    }
    return 0;
}

static char *test_empty_board()
{
    struct ChessBoard board;
    createBoard(&board);
    for (int i = 0; i < 8 * 8; i++)
    {
        mu_assert("Value in empty chess board is not 0", board.tiles[i] == 0);
    }
    return 0;
}

static char *test_algebraic_to_index()
{
    int index;
    algebraicToIndex("a8", &index);
    mu_assert("a8 is not converted to index 0", index == 0);

    algebraicToIndex("h1", &index);
    mu_assert("h1 is not converted to index 63", index == 63);

    algebraicToIndex("d6", &index);
    mu_assert("d6 is not converted to index 19", index == 19);

    return 0;
}

static char *all_tests()
{
    mu_run_test(test_empty_board);
    mu_run_test(test_algebraic_to_index);
    mu_run_test(test_empty_fen);
    mu_run_test(test_en_passant_fen);
    mu_run_test(test_start_fen);
    mu_run_test(test_fen_1);
    return 0;
}

int main(int argc, char **argv)
{
    char *result = all_tests();
    if (result != 0)
    {
        printf("%s\n", result);
    }
    else
    {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}