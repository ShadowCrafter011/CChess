#include <stdio.h>
#include "board.c"

int main()
{
    struct ChessBoard board;
    createBoard(&board);
    destructBoard(&board);
    return 0;
}
