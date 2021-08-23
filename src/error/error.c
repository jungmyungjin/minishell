# include "../../minishell.h"

/*
 * refer error code: https://www.geeksforgeeks.org/exit-codes-in-c-c-with-examples/
 */
int allocation_error()
{
    printf("Error: memory allocation failure\n");
    exit(137); // a program took up too much memory
}
