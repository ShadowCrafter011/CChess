#include <stdlib.h>
#include "munit.h"
#include "test_fen.h"
#include "test_board.h"
#include "test_list.h"
#include "test_moves.h"

static MunitTest tests[] = {
    { "/fen/test-fen-1", test_fen_1, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/fen/test-start-fen", test_start_fen, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/fen/test-en-passant-fen", test_en_passant_fen, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/fen/test-empty-fen", test_empty_fen, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/board/test-empty-board", test_empty_board, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/board/test-algebraic-to-index", test_algebraic_to_index, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/board/test-play-move", test_play_move, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/list/test-list", test_list, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/moves/test-startpos-perft", test_startpos_perft, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = { "", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE };

int main(int argc, char *argv[])
{
    return munit_suite_main(&suite, NULL, argc, argv);
}
