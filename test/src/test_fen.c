#include "test_fen.h"
#include "fen.h"
#include "piece.h"

MunitResult test_fen_1(const MunitParameter params[], void* data)
{
    (void) params;
    (void) data;
    
    struct ChessBoard board;
    create_board(&board);
    load_fen(&board, "rnb2bnr/ppppkppp/8/4p1q1/P1PP3P/R2Q4/1P2PPP1/1NB1KBNR b K c3 158 1000");

    bool K = false, Q = false, k = false, q = false;
    check_castling(&board, &K, &Q, &k, &q);
    munit_assert(K); // White cannot king side castle for fen 1 
    munit_assert(!Q); // White can queen side castle for fen 1
    munit_assert(!k); // Black can king side castle for fen 1
    munit_assert(!q); // Black can queen side castle for fen 1

    munit_assert_int(board.en_passant_target, ==, 42); // En passant target is not 42 target c3 for fen 1

    munit_assert_char(board.active_color, ==, 'b'); // It is not blacks turn to move fen 1

    munit_assert_int(board.half_move_clock, ==, 158); // Halfmove clock is not 158 for fen 1
    munit_assert_int(board.full_move_clock, ==, 1000); // Fullmove clock is not 1000 for fen 1

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
        munit_assert_int(board.tiles[i], ==, expected[i]); // Board does not match expected values for fen 1
    }

    return MUNIT_OK;
}

MunitResult test_start_fen(const MunitParameter params[], void* data)
{
    (void) params;
    (void) data;

    struct ChessBoard board;
    create_board(&board);
    load_fen(&board, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    munit_assert_char(board.active_color, ==, 'w'); // It is not whites turn for start fen

    bool black_king_side_castle, black_queen_side_castle, white_king_side_castle, white_queen_side_castle;
    check_castling(&board, &white_king_side_castle, &white_queen_side_castle, &black_king_side_castle, &black_queen_side_castle);
    munit_assert(black_king_side_castle); // Black cannot castle king side for start fen
    munit_assert(black_queen_side_castle); // Black cannot castle queen side for start fen
    munit_assert(white_king_side_castle); // White cannot castle king side for start fen
    munit_assert(white_queen_side_castle); // White cannot castle queen side for start fen

    munit_assert_int(board.en_passant_target, ==, -1); // There is an en passant target square for start fen

    munit_assert_int(board.half_move_clock, ==, 0); // The halfmove clock is not 0 for start fen
    munit_assert_int(board.full_move_clock, ==, 1); // The fullmove clock is not 1 for start fen

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
        munit_assert_int(board.tiles[i], ==, expected[i]); // Board does not match expected values for start fen
    }
    
    return MUNIT_OK;
}

MunitResult test_en_passant_fen(const MunitParameter params[], void* data)
{
    (void) params;
    (void) data;

    struct ChessBoard board;
    create_board(&board);
    load_fen(&board, "8/8/8/8/8/8/8/8 w - a8 0 1");
    munit_assert_int(board.en_passant_target, ==, 0); // En passant target is not index 0 for a8 fen
    load_fen(&board, "8/8/8/8/8/8/8/8 w - h1 0 1");
    munit_assert_int(board.en_passant_target, ==, 63); // En passant target is not index 63 for h1 fen

    return MUNIT_OK;
}

MunitResult test_empty_fen(const MunitParameter params[], void* data)
{
    (void) params;
    (void) data;

    struct ChessBoard board;
    create_board(&board);
    load_fen(&board, "8/8/8/8/8/8/8/8 w - - 0 1");
    for (int i = 0; i < 8 * 8; i++)
    {
        munit_assert_int(board.tiles[i], ==, 0); // Value in empty chess board loaded by fen is not 0
    }

    return MUNIT_OK;
}
