enum ChessPiece
{
    EMPTY = 0,
    WHITE_PAWN,
    WHITE_KNIGHT,
    WHITE_BISHOP,
    WHITE_ROOK,
    WHITE_QUEEN,
    WHITE_KING,
    BLACK_PAWN,
    BLACK_KNIGHT,
    BLACK_BISHOP,
    BLACK_ROOK,
    BLACK_QUEEN,
    BLACK_KING
};

int charToChessPiece(char *piece_char, int *out)
{
    switch (*piece_char)
    {
        case 'p':
            *out = BLACK_PAWN;
            break;
        case 'n':
            *out = BLACK_KNIGHT;
            break;
        case 'b':
            *out = BLACK_BISHOP;
            break;
        case 'r':
            *out = BLACK_ROOK;
            break;
        case 'q':
            *out = BLACK_QUEEN;
            break;
        case 'k':
            *out = BLACK_KING;
            break;
        case 'P':
            *out = WHITE_PAWN;
            break;
        case 'N':
            *out = WHITE_KNIGHT;
            break;
        case 'B':
            *out = WHITE_BISHOP;
            break;
        case 'R':
            *out = WHITE_ROOK;
            break;
        case 'Q':
            *out = WHITE_QUEEN;
            break;
        case 'K':
            *out = WHITE_KING;
            break;
    }
    return 0;
}
