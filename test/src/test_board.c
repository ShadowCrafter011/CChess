#include "test_board.h"
#include "board.h"
#include "fen.h"
#include "piece.h"

MunitResult test_empty_board(const MunitParameter params[], void* data)
{
    (void) params;
    (void) data;

    struct ChessBoard board;
    create_board(&board);
    for (int i = 0; i < 8 * 8; i++)
    {
        munit_assert_int(board.tiles[i], ==, 0); // Value in empty chess board is not 0
    }

    return MUNIT_OK;
}

MunitResult test_algebraic_to_index(const MunitParameter params[], void* data)
{
    (void) params;
    (void) data;

    int index = algebraic_to_index("a8");
    munit_assert_int(index, ==, 0); // a8 is not converted to index 0

    index = algebraic_to_index("h1");
    munit_assert_int(index, ==, 63); // h1 is not converted to index 63

    index = algebraic_to_index("d6");
    munit_assert_int(index, ==, 19); // d6 is not converted to index 19

    return MUNIT_OK;
}

MunitResult test_play_move(const MunitParameter params[], void* data)
{
    (void) params;
    (void) data;

    ChessBoard board;
    create_board(&board);
    load_fen(&board, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    play_move_algebraic(&board, "a2a4");
    play_move_algebraic(&board, "d7d5");
    play_move_algebraic(&board, "b1c3");
    play_move_algebraic(&board, "c8g4");
    play_move_algebraic(&board, "c3d5");
    play_move_algebraic(&board, "d8d5");
    play_move_algebraic(&board, "e2e4");
    play_move_algebraic(&board, "d5e4");

    int expected[64] = {
        BLACK_ROOK, BLACK_KNIGHT, EMPTY, EMPTY, BLACK_KING, BLACK_BISHOP, BLACK_KNIGHT, BLACK_ROOK,
        BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, EMPTY, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN,
        EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
        EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
        WHITE_PAWN, EMPTY, EMPTY, EMPTY, BLACK_QUEEN, EMPTY, BLACK_BISHOP, EMPTY,
        EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
        EMPTY, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, EMPTY, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN,
        WHITE_ROOK, EMPTY, WHITE_BISHOP, WHITE_QUEEN, WHITE_KING, WHITE_BISHOP, WHITE_KNIGHT, WHITE_ROOK
    };

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        munit_assert_int(board.tiles[i], ==, expected[i]);
    }

    // Three pieces were captured so we only care about the first 29 elements
    int piece_index_expected[29] = {
        BLACK_ROOK, BLACK_KNIGHT, BLACK_BISHOP, BLACK_QUEEN, BLACK_KING, BLACK_BISHOP, BLACK_KNIGHT, BLACK_ROOK,
        BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN,
        WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN,
        WHITE_ROOK, WHITE_BISHOP, WHITE_QUEEN, WHITE_KING, WHITE_BISHOP, WHITE_KNIGHT, WHITE_ROOK
    };

    for (int i = 0; i < 29; i++)
    {
        munit_assert_int(board.tiles[board.piece_indices[i]], ==, piece_index_expected[i]); // Check that the piece index array was filled correctly
    }

    return MUNIT_OK;
}
