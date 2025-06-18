CC := gcc
CFLAGS := -Wall -Wextra -std=c99 -Iinclude -Itest/include -Itest/munit

SRC := src/board.c src/fen.c src/uci.c src/piece.c src/perft.c src/moves.c src/list.c
TEST_SRC := test/test.c test/munit/munit.c test/src/test_fen.c test/src/test_board.c test/src/test_moves.c test/src/test_list.c
TEST_OBJS := $(TEST_SRC:.c=.o)
BUILD_DIR := build

ENGINE_BIN := $(BUILD_DIR)/engine
TEST_BIN := $(BUILD_DIR)/test

.PHONY: all run test clean

all: $(ENGINE_BIN)

run: $(ENGINE_BIN)
	./$(ENGINE_BIN)

test: $(TEST_BIN)
	./$(TEST_BIN)

$(ENGINE_BIN): src/main.c $(SRC)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(TEST_BIN): $(SRC) $(TEST_SRC)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf $(BUILD_DIR) *.o test/*.o src/*.o
