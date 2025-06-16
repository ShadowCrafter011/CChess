#include <stdio.h>

int run_uci()
{
    while (1)
    {
        char uci_command[100];
        scanf("%[^\n]s", uci_command);
        printf("UCI command %s\n", uci_command);
    }
    return 0;
}
