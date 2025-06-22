#ifndef TEST_BOARD_H
#define TEST_BOARD_H

#include "munit.h"

MunitResult test_empty_board(const MunitParameter params[], void* data);

MunitResult test_algebraic_to_index(const MunitParameter params[], void* data);

MunitResult test_play_move(const MunitParameter params[], void* data);

#endif