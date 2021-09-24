
#include "minishell.h"

// 자식 프로세서에서 실행
void exec_external_set_pipe(t_mcb *mcb)
{
    if (mcb->pre_pipe_check == 1) // 이전 프로세서의 아웃풋을 => 현재 파이프의 안풋으로 사용
    {
        if (mcb->pipe_read_end != STDIN_FILENO) // STDIN_FILENO은 close 되면 안되서 if문 사용
        {
            dup2(mcb->pipe_read_end, STDIN_FILENO); // 파이프 에서 읽어서 => 현재 프로세스 인풋으로
            close(mcb->pipe_read_end); // STDIN_FILENO은 되면 안됨
        }
    }
    if (mcb->next_pipe_check == 1) // 파이프 체크가 1일 경우. 다음에 파이프가 있으므로 전달해줘야함
    {
        close(mcb->fd[READ_END]); // 자식 프로세스에서 읽기는 사용하지 않음.
        dup2(mcb->pipe_write_end, STDOUT_FILENO); // 현재 프로세스 아웃풋을 => 파이프로 보냄
        close(mcb->pipe_write_end);
    }
}

void exec_external_file_close(t_mcb *mcb)
{
    if (mcb->fd_input != STDIN_FILENO)
        close(mcb->fd_input);
    if (mcb->fd_output != STDOUT_FILENO)
        close(mcb->fd_output);
}

void exec_external_stdout_stdin(t_mcb *mcb)
{
    if (mcb->fd_input != STDIN_FILENO) // 기본 인풋 변경함
        dup2(mcb->fd_input, STDIN_FILENO); // 두번재 인자가 열려있으면 닫은 후 복제됨
    if (mcb->fd_output != STDOUT_FILENO) // 아웃풋 변경, 자식의 모든 출력을 변경 stdout -> file 복사됨
        dup2(mcb->fd_output, STDOUT_FILENO);
}

void exec_external_close_pipe(t_mcb *mcb)
{
    if (mcb->pre_pipe_check == 1)
    {
        close(mcb->pipe_read_end); // 이전 파이프를 읽엇으므로 close
        mcb->pre_pipe_check = 0;
    }
    if (mcb->next_pipe_check == 1) // 다음에 파이프가 있을 경우
    {
        close(mcb->fd[WRITE_END]); // 부모 프로세스에서 쓰기를 사용하지 않음
        mcb->next_pipe_check = 0;
        mcb->pipe_read_end = mcb->fd[READ_END];
        mcb->pre_pipe_check = 1; // 이제부터 파이프과 과거에 있음을 플래그 표시
    }
}

void execute_external(t_ast *node, t_list *env, t_mcb *mcb)
{
	extern char **environ;

	if (execve(((t_simple_cmd*)node->data)->file_path, ((t_simple_cmd*)node->data)->argv, environ) == -1)	// 바이너리 교체 실패
	{
		global.rtn = 127;
		ft_putendl_fd("Command not found", STDERR_FILENO);
		exit(0);
	}
}

int	execute_set_built_in(t_simple_cmd *simple_cmd, t_list *env, t_mcb *mcb)
{
	if (!ft_strcmp(simple_cmd->original, "exit"))
	{
		ft_exit(simple_cmd, env, mcb);
		return (1);
	}
	if (!ft_strcmp(simple_cmd->original, "unset"))
	{
		ft_unset(simple_cmd, env, mcb);
		return (1);
	}
	if (!ft_strcmp(simple_cmd->original, "cd"))
	{
		ft_cd(simple_cmd, env, mcb);
		return (1);
	}
	if (!ft_strcmp(simple_cmd->original, "export") && simple_cmd->argv[1] != NULL)
	{
		ft_export(simple_cmd, env, mcb);
		return (1);
	}
	return (0);
}

void execute_print_built_in(t_simple_cmd *simple_cmd, t_list *env, t_mcb *mcb)
{
	if (!ft_strcmp(simple_cmd->original, "env"))
		ft_env(simple_cmd, env, mcb);
	if (!ft_strcmp(simple_cmd->original, "export"))
		ft_export(simple_cmd, env, mcb);
	if (!ft_strcmp(simple_cmd->original, "pwd"))
		ft_pwd(simple_cmd, env, mcb);
	if (!ft_strcmp(simple_cmd->original, "echo"))
		ft_echo(simple_cmd, env, mcb);
}

void run_using_fork(t_ast *node, t_list *env, t_mcb *mcb)
{
	pid_t pid;
	pid_t wpid;
	int status;

	pid = fork();	// 새로운 자식 프로세스 생성
	if (pid == 0)	// 자식 프로세스
	{
		exec_external_set_pipe(mcb);
		exec_external_stdout_stdin(mcb);
		if (is_built_in(node->data))
			execute_print_built_in(node->data, env, mcb);
		else
			execute_external(node, env, mcb);
	}
	else if (pid > 0)	// 부모 프로세스
	{
		wpid = waitpid(pid, &status, WUNTRACED);
		exec_external_close_pipe(mcb);
		exec_external_file_close(mcb);
	}
	else
		ft_putendl_fd("Pid error", STDERR_FILENO);
}

void	execute_command(t_ast *node, t_list *env, t_mcb *mcb)
{
	if (execute_set_built_in(node->data, env, mcb) == 1)
		return;
	global.child = 1;
	run_using_fork(node, env, mcb);
	global.child = 0;
}