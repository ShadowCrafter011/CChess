#include <stdlib.h>
#include "munit.h"
#include "test_fen.h"
#include "test_board.h"

static MunitTest fen_tests[] = {
    { "/test-fen-1", test_fen_1, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test-start-fen", test_start_fen, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test-en-passant-fen", test_en_passant_fen, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test-empty-fen", test_empty_fen, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static MunitTest board_tests[] = {
    { "/test-empty-board", test_empty_board, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test-algebraic-to-index", test_algebraic_to_index, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static MunitSuite suites[] = {
    { "/fen", fen_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE },
    { "/board", board_tests, NULL, 1, MUNIT_SUITE_OPTION_NONE },
    { NULL }
};

static const MunitSuite suite = { "", NULL, suites, 1, MUNIT_SUITE_OPTION_NONE };

int main(int argc, char *argv[])
{
    return munit_suite_main(&suite, NULL, argc, argv);
}
