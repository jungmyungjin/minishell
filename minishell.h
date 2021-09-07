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
# include "libft/libft.h"
#include <sys/stat.h>

# define SHELL_NAME "minishell"

int main(int argc, char *argv[], char *envp[]);

/*
 * token
 */

# define T_WORD 0
# define T_PIPE 1
# define T_REDIRECT 2
typedef struct s_token {
    int type;
    char *str;
} t_token;

typedef struct s_token_info {
    int count;
    t_token *tokens;
} t_token_info;


/*
 * AST
 */
typedef struct s_args {
    char **args;
} t_args;

typedef struct s_simple_cmd {
    char *filename;
    t_args *args;
} t_simple_cmd;

// https://www.gnu.org/software/bash/manual/html_node/Redirections.html
# define INPUT 0 // <
# define OUTPUT 1 // >
# define HERE_DOCUMENTS 2 // <<
# define APPENDING_OUTPUT 3// >>
typedef struct s_redirect {
    int type;
    char *filename;
} t_redirect;

typedef struct s_cmd {
    t_simple_cmd simple_cmd;
    t_redirect redirect;
} t_cmd;

#define CMD 0
#define PIPE 1 // '|'
typedef struct s_abstract_syntax {
    int type;
    void *data;
} t_as;

// tree is contained in abstract_syntax
typedef struct s_btree {
    t_as *as;
    struct s_btree *left;
    struct s_btree *right;
} t_btree;

/*
 * parser
 */
int 	lexical_analysis(t_list *env, char *line, t_token_info *token_info);
int    tokenizer_split(char *line, t_token_info *token_info);
void	convert_env(t_list *env, t_token_info *token_info);
void    set_tokenizer_type(t_token_info *token_info);
/*
 * env utils
 */

/*
 * utils
 */
int	ft_strcmp(char *s1, char *s2);

/*
 * exception
 */
int	quotes_exception();


/*
 * error
 */
int	allocation_error();
void env_key_error(char *cmd, char *arg);


/*
 *  built-in
 */
void	ft_cd();
void	ft_env(t_list *env);
void	ft_export(t_list **env, char *key, char *value);
char	*ft_pwd();
void	ft_unset(t_list **env, char *target_key);
char	*get_current_path(void);




/*
 *  env
 */

typedef struct s_env
{
	char *origin_text;
	char *key;
	char *value;
}	t_env;
t_env	*envnew(void);
void	set_env_key_value(char *origin_text, char **key, char **value);
void	env_initialize(t_list **env, char **envp);
char	*get_env_value(t_list *env, char *env_key);
void	set_env(t_list **env, char *key, char *value);
void	unset_env(t_list **env_list, char *target_key);
int	check_env_key(char *key);
char	*get_full_path_by_env(t_list *env, char *filename);

/*
 *  execute
 */
int	exec_external(t_list *env);

#endif
