#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>	// chdir()
# include <signal.h>
# include <string.h> // strerror()
# include <errno.h> // variable errno

int main(int argc, char *argv[], char *envp[]);


/*
 * parser
 */
char **tokenizer(char *line);
char **tokenizer_split(char *line);

void	*free_tokens(char **ptr, size_t size);


/*
 * exception
 */
int quotes_exception();


/*
 * error
 */
int allocation_error();

#endif
