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


typedef struct s_token {
    int token_count;
    char **tokens;
} t_token;

/*
 * parser
 */
char **tokenizer(char *line);
t_token tokenizer_split(char *line);
void    convert_env(t_token token_info);

/*
 * env utils
char *get_env_value(char *env_key);


/*
 * utils
 */
int	ft_strcmp(char *s1, char *s2);

/*
 * exception
 */
int quotes_exception();


/*
 * error
 */
int allocation_error();

#endif
