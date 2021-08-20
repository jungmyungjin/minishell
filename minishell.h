#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
# include <libft.h>

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
