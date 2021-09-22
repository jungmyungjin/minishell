#include "../minishell.h"

// return
// not found: NULL
// found: full_path
char *get_full_path(t_list *env, char *cmd)
{
    char *current_path;
    char *full_path;

    if (ft_strncmp(cmd, "/", 1) == 0)
	{
		full_path = ft_strdup(cmd);
	}
    else if (ft_strncmp("./", cmd, 2) == 0)
    {
        cmd = ft_substr(cmd, 2, ft_strlen(cmd) - 2);
        current_path = get_current_path();
        full_path = ft_strjoin(current_path, ft_strdup("/"));
        full_path = ft_strjoin(full_path,cmd);
    }
    else
    {
        full_path = get_full_path_by_env(env, cmd);
    }
    return(full_path);
}

void set_simple_cmd_full_path(t_list *env, t_simple_cmd *simple_cmd)
{
    simple_cmd->file_path = get_full_path(env, simple_cmd->original);
}

void set_full_path_in_tree(t_list *env, t_ast *node)
{
    if (node->left != NULL)
        set_full_path_in_tree(env, node->left);
    if (node->right != NULL)
        set_full_path_in_tree(env, node->right);
    if (node->type == AST_SIMPLE_CMD)
        set_simple_cmd_full_path(env, node->data);
}

// tree 형태로 파싱
t_ast *parser(t_list *env, char *line)
{
    t_token_info tokens;
    t_ast *root;
    int result;

    result = lexical_analysis(env, line, &tokens);
    if (result == -1) // 토큰화 실패.
        return (NULL);

//    for (int i = 0; i<=tokens.count; i++)
//        printf("index: %d, str: %s, type: %d\n", i, tokens.tokens[i].str, tokens.tokens[i].type);

    // 문법 체크 및 tree 로
    root = NULL;
    result = syntax_analysis(tokens, &root);
    if (result == -1 || root == NULL) // 문법 체크 실패
    {
        free_tokens(&tokens);
        return (NULL);
    }
    set_full_path_in_tree(env, root);
    free_tokens(&tokens);
    return root;
}


void init_mcb(t_mcb *mcb)
{
    mcb->next_pipe_check = 0;
    mcb->pre_pipe_check = 0;
    mcb->pipe_read_end = STDIN_FILENO;
    mcb->pipe_write_end = STDOUT_FILENO;
    mcb->fd_input = STDIN_FILENO;
    mcb->fd_output = STDOUT_FILENO;
}

void minishell_loop(t_list **env)
{
	char *line;
	t_ast *root;
	t_mcb mcb;

	set_signal();
	while (1)
	{
		line = readline(">> ");
		if (line == NULL)
		    sig_exit_shell();
		root = parser(*env, line); // 파서 시작.
		if (root != NULL)
		{
		    init_mcb(&mcb);
		    search_tree(root, *env, &mcb);
		    free_tree(&root);
		}
		if (ft_strcmp(line, ""))
		    add_history(line); // up down key
		free(line);
	}
}

int main(int argc, char *argv[], char *envp[])
{
	t_list *env;

	if(argc||argv||envp)	// gcc 컴파일 에러처리를 위함
		;
	env_initialize(&env, envp);
	minishell_loop(&env);
	return (EXIT_SUCCESS);
}
