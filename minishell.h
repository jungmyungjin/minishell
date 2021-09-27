#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# include "libft/libft.h"
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>

# define SHELL_NAME "minishell"

# define READ_END 0
# define WRITE_END 1
typedef struct s_common {
	int	child;
	int	rtn;
}	t_common;

t_common	g_global;

int	main(int argc, char *argv[], char *envp[]);

/*
 * token
 */

# define T_NULL 0
# define T_WORD 1
# define T_PIPE 2
# define T_REDIRECT 3
# define T_DOUBLE_QUOTES 4
# define T_SINGLE_QUOTES 5
typedef struct s_token {
	int		type;
	char	*str;
}	t_token;

typedef struct s_token_info {
	int		count;
	t_token	*tokens;
}	t_token_info;

/*
 * AST
 */
# define AST_PIPE 1
# define AST_CMD 2
# define AST_SIMPLE_CMD 3
# define AST_REDIRECTS 4
# define AST_REDIRECT 5
typedef struct s_abstract_syntax_tree {
	int								type;
	void							*data;
	struct s_abstract_syntax_tree	*left;
	struct s_abstract_syntax_tree	*right;
}	t_ast;

typedef struct s_simple_cmd {
	char	*original;
	char	*file_path;
	char	**argv;
}	t_simple_cmd;

# define INPUT 1 // <
# define OUTPUT 2 // >
# define HERE_DOCUMENTS 3 // <<
# define APPENDING_OUTPUT 4// >>
typedef struct s_redirect {
	int		type;
	char	*filename;
}	t_redirect;

/*
 * execute cmd
 */
typedef struct s_minishell_control_block {
	int	fd[2];
	int	pipe_read_end;
	int	pipe_write_end;
	int	next_pipe_check;
	int	pre_pipe_check;
	int	heredoc_count;
	int	fd_input;
	int	fd_output;
}	t_mcb;

/*
 * parser lexical analysis
 */
t_token	*split_line(const char *line, t_token *tokens, int count);
char	**tokenizer(t_list *env, char *line);
int	lexical_analysis(t_list *env, char *line, t_token_info *token_info);
int	tokenizer_split(char *line, t_token_info *token_info);
int	counting_tokens(char *line);
int	find_quotes_to_end(const char *line, int i, t_token *token);
int	find_double_quotes(const char *line, int i);
int	find_single_quotes(const char *line, int i);
int	is_space(char c);
void	convert_env(t_list *env, t_token_info *token_info);
void	set_tokenizer_type(t_token_info *token_info);
void	free_tokens(t_token_info *token_info);

/*
 * parser syntax analysis
 */
int syntax_analysis(t_token_info tokens, t_ast **root);
int syntax_pipeline(t_token_info tokens, int idx, t_ast **node);
int syntax_cmd(t_token_info tokens, int idx, t_ast **node);
int syntax_simple_cmd(t_token_info tokens, int idx, t_ast **node);
int syntax_argv(t_token_info tokens, int idx, char **args, int depth);
int syntax_redirects(t_token_info tokens, int idx, t_ast **node);
int syntax_io_redirect(t_token_info tokens, int idx, t_ast **node);
int	add_simple_cmd_argv(t_token_info tokens, t_simple_cmd *simple_cmd, int idx);
int syntax_pipeline_check(t_token_info tokens, int idx);
int syntax_cmd_check(t_token_info tokens, int idx);
int syntax_simple_cmd_check(t_token_info tokens, int idx);
int syntax_redirects_check(t_token_info tokens, int idx);
int syntax_io_redirect_check(t_token_info tokens, int idx);
int redirect_type(char *str);

t_ast	*new_ast(void *item, int type);
void free_tree(t_ast **node);

/*
 * full path
 */
char	*get_full_path(t_list *env, char *cmd);
void	set_simple_cmd_full_path(t_list *env, t_simple_cmd *simple_cmd);
void	set_full_path_in_tree(t_list *env, t_ast *node);


/*
 * utils
 */
int	ft_strcmp(char *s1, char *s2);
void	set_wpid_status(int status);
void	set_execve_status(void);

/*
 * exception
 */
int	quotes_exception(void);

/*
 * error
 */
int	allocation_error(void);
void	env_key_error(char *cmd, char *arg);

/*
 *  built-in
 */
void	ft_cd(t_simple_cmd *simple_cmd, t_list *env, t_mcb *mcb);
void	ft_env(t_simple_cmd *simple_cmd, t_list *env, t_mcb *mcb);
void	ft_export(t_simple_cmd *simple_cmd, t_list *env, t_mcb *mcb);
void	ft_pwd(t_simple_cmd *simple_cmd, t_list *env, t_mcb *mcb);
void	ft_unset(t_simple_cmd *simple_cmd, t_list *env, t_mcb *mcb);
void	ft_echo(t_simple_cmd *simple_cmd, t_list *env, t_mcb *mcb);
void	ft_exit(t_simple_cmd *simple_cmd, t_list *env, t_mcb *mcb);

char	*get_current_path(void);

/*
 * signal
 */
void set_signal(void);
void sig_exit_shell(void);


/*
 *  env
 */

typedef struct s_env
{
	char *origin_text;
	char *key;
	char *value;
}	t_env;
int	allowed_character(char *string);
int	check_env_key(char *key);
int	is_env_character(char c);
int	is_env(char *str, int i);
void	free_double_char(char **lines);
char	**get_env_path(t_list *env);
char	*get_full_path_by_env(t_list *env, char *filename);
void	free_double_char(char **lines);
char	**get_env_path(t_list *env);
char	*get_full_path_by_env(t_list *env, char *filename);
t_env	*find_env_by_key(t_list *env, char *env_key);
char	*get_env_value(t_list *env, char *env_key);
t_env	*envnew(void);
void	set_env_key_value(char *origin_text, char **key, char **value);
void	env_initialize(t_list **env, char **envp);
void	set_env_value(t_env *env, char *key, char *value);
void	set_new_env(t_list **env, char *key, char *value);
void	set_env(t_list **env, char *key, char *value);
void	free_env_list(t_list **target);
void	delete_list_by_key(t_list **all_list, t_list *prev, t_list *current);
void	unset_env(t_list **env_list, char *target_key);

/*
 *  execute
 */
void	execute_external(t_ast *node, t_list *env, t_mcb *mcb);
int	execute_set_built_in(t_simple_cmd *simple_cmd, t_list *env, t_mcb *mcb);
void	execute_print_built_in(
		t_simple_cmd *simple_cmd, t_list *env, t_mcb *mcb);
void	run_using_fork(t_ast *node, t_list *env, t_mcb *mcb);
void	execute_command(t_ast *node, t_list *env, t_mcb *mcb);
void	redirect_output(char *filename, t_mcb *mcb);
void	redirect_append(char *filename, t_mcb *mcb);
void	redirect_input(char *filename, t_mcb *mcb);
void	redirect_heredoc(char *eof_keyword, t_mcb *mcb);
void	execute_redirect(t_redirect *redirect, t_mcb *mcb);
int	is_built_in(t_simple_cmd *simple_cmd);
void	init_mcb_in_execute(t_mcb *mcb);
void	next_pipe_check(t_ast *node, t_mcb *mcb);
void	execute_tree(t_ast *node, t_list *env, t_mcb *mcb);
void	search_tree(t_ast *node, t_list *env, t_mcb *mcb);
void	execve_built_in(t_simple_cmd *simple_cmd, t_list *env, t_mcb *mcb);
void	exec_external_set_pipe(t_mcb *mcb);
void	exec_external_file_close(t_mcb *mcb);
void	exec_external_stdout_stdin(t_mcb *mcb);
void	exec_external_close_pipe(t_mcb *mcb);

#endif
