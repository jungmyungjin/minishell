# include "../../minishell.h"

/*
 * refer error code: https://www.geeksforgeeks.org/exit-codes-in-c-c-with-examples/
 */
int allocation_error()
{
    printf("Error: memory allocation failure\n");
	global.rtn = 137;
    exit(137); // a program took up too much memory
}


void env_key_error(char *cmd, char *arg)
{
	char *error_msg;

	error_msg = "not a valid identifier";

	// bash: export: `$%%abc': not a valid  identifier
	ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": '", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("'", STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(error_msg, STDERR_FILENO);
}
