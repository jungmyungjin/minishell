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

# define T_NULL 0
# define T_WORD 1
# define T_PIPE 2
# define T_REDIRECT 3
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
#define AST_PIPE 1 // '|'
#define AST_CMD 2
#define AST_SIMPLE_CMD 3
#define AST_REDIRECTS 4 // '<'
#define AST_REDIRECT 5
typedef struct s_abstract_syntax_tree {
    int type;
    void *data;
    struct s_abstract_syntax_tree *left;
    struct s_abstract_syntax_tree *right;
} t_ast;

typedef struct s_simple_cmd {
    char *cmd_name;
    char **args;
} t_simple_cmd;

// https://www.gnu.org/software/bash/manual/html_node/Redirections.html
# define INPUT 1 // <
# define OUTPUT 2 // >
# define HERE_DOCUMENTS 3 // <<
# define APPENDING_OUTPUT 4// >>
typedef struct s_redirect {
    int type;
    char *filename;
} t_redirect;

/*
 * parser lexical analysis
 */
char	**tokenizer(t_list *env, char *line);
int 	lexical_analysis(t_list *env, char *line, t_token_info *token_info);
int    tokenizer_split(char *line, t_token_info *token_info);
void	convert_env(t_list *env, t_token_info *token_info);
void    set_tokenizer_type(t_token_info *token_info);
void    free_tokens(t_token_info *token_info);

/*
 * parser syntax analysis
 */
int syntax_analysis(t_token_info tokens, t_ast **root);
int syntax_pipeline(t_token_info tokens, int idx, t_ast **node);
int syntax_cmd(t_token_info tokens, int idx, t_ast **node);
int syntax_simple_cmd(t_token_info tokens, int idx, t_ast **node);
int syntax_args(t_token_info tokens, int idx, char **args, int depth);
int syntax_redirects(t_token_info tokens, int idx, t_ast **node);
int syntax_io_redirect(t_token_info tokens, int idx, t_ast **node);

int syntax_pipeline_check(t_token_info tokens, int idx);
int syntax_cmd_check(t_token_info tokens, int idx);
int syntax_simple_cmd_check(t_token_info tokens, int idx);
int syntax_redirects_check(t_token_info tokens, int idx);
int syntax_io_redirect_check(t_token_info tokens, int idx);

int redirect_type(char *str);

t_ast	*new_ast(void *item, int type);
void free_tree(t_ast **node);

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
t_env	*find_env_by_key(t_list *env, char *env_key);


/*
 *  execute
 */
int	exec_external(t_list *env);

#endif
