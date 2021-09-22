
#include "minishell.h"

int	is_built_in(t_simple_cmd *simple_cmd)
{
    if (!ft_strcmp(simple_cmd->original, "cd"))
        return (1);
    if (!ft_strcmp(simple_cmd->original, "env"))
        return (1);
    if (!ft_strcmp(simple_cmd->original, "export"))
        return (1);
    if (!ft_strcmp(simple_cmd->original, "unset"))
        return (1);
    if (!ft_strcmp(simple_cmd->original, "pwd"))
        return (1);
	if (!ft_strcmp(simple_cmd->original, "echo"))
		return (1);
	if (!ft_strcmp(simple_cmd->original, "exit"))
		return (1);
    return (0);
}

void exec_run_type(t_ast *node, t_list *env, t_mcb *mcb)
{
    g_child = 1;
    if (is_built_in(node->data))
        execve_built_in(node->data, env);
    else
        exec_external(node->data, env, mcb);
    g_child = 0;
}

void init_mcb_in_execute(t_mcb *mcb)
{
    if (mcb->fd_input != STDIN_FILENO)
        dup2(STDIN_FILENO, mcb->fd_input);
    if (mcb->fd_output != STDOUT_FILENO) // cmd 들어가기전에 stdout로 변경
        dup2(STDOUT_FILENO, mcb->fd_output);
}

void next_pipe_check(t_ast *node, t_mcb *mcb)
{
    int pipe_status;

    // 다음에 또 파이프가 있는가? 있으면 파이프 pipe 를 생성함!
    if (node->right != NULL && node->right->type == AST_PIPE)
    {
        pipe_status = pipe(mcb->fd);
        if (pipe_status < 0)
        {
            ft_putendl_fd("PIPE FD ERROR", STDERR_FILENO);
            exit(EXIT_FAILURE); // todo: 실패시 return 할지 종료할지 결졍 필요.
        }
        mcb->pipe_write_end = mcb->fd[WRITE_END]; // pipe_write_end 을 복사.
        mcb->next_pipe_check = 1;
    }
}

void execute_tree(t_ast *node, t_list *env, t_mcb *mcb)
{
    if (node->type == AST_PIPE)
        next_pipe_check(node, mcb);
    if (node->type == AST_REDIRECT)
        execute_redirect(node->data, mcb); // redirects -> redirect -> t_redirect
    if (node->type == AST_CMD)
        init_mcb_in_execute(mcb);
    if (node->type == AST_SIMPLE_CMD)
        exec_run_type(node, env, mcb);
}

// 전위 탐색
void search_tree(t_ast *node, t_list *env, t_mcb *mcb)
{
    execute_tree(node, env, mcb);
    if (node->left != NULL)
        search_tree(node->left, env, mcb);
    if (node->right != NULL)
        search_tree(node->right, env, mcb);
}
