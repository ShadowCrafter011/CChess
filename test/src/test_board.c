#include "test_board.h"
#include "board.h"

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

    int index;
    algebraic_to_index("a8", &index);
    munit_assert_int(index, ==, 0); // a8 is not converted to index 0

    algebraic_to_index("h1", &index);
    munit_assert_int(index, ==, 63); // h1 is not converted to index 63

    algebraic_to_index("d6", &index);
    munit_assert_int(index, ==, 19); // d6 is not converted to index 19

    return MUNIT_OK;
}
