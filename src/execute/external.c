
#include "minishell.h"

void exec_external_set_pipe(t_mcb *mcb)
{
    if (mcb->next_pipe_check == 1) // 파이스 체크가 1일 경우. 이전 파이프가 있엇다는 이야기
        ;// set_pipe(mcb);;
    // 이전 파이프에 있던 내용을 가져와서
    // dup2(mcb->fd[STDOUT_FILENO], STDOUT_FILENO);

    // 자식 프로세서의 인풋 => 파이프의 아웃으로

    // 이전 프로세서의 아웃풋을 => 현재 파이프의 안풋으로
    // dup2(mcb->fd[STDOUT_FILENO], STDOUT_FILENO);
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

int	exec_external(t_simple_cmd *simple_cmd, t_list *env, t_mcb *mcb)
{
	extern char **environ;
	pid_t pid, wpid;
	int status;

	pid = fork();	// 새로운 자식 프로세스 생성
	if (pid == 0)	// 자식 프로세스
	{
        exec_external_set_pipe(mcb);
        exec_external_stdout_stdin(mcb);
		if (execve(simple_cmd->file_path, simple_cmd->argv, environ) == -1)	// 바이너리 교체 실패
        {
		    ft_putendl_fd("ERROR", STDERR_FILENO);
		    exit(EXIT_FAILURE);
        }
	}
	else if (pid > 0)	// 부모 프로세스
	{
		do
		{	// 부모프로세스는 자식프로세스가 종료될때 까지 기다린다
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	else
		ft_putendl_fd("ERROR", STDERR_FILENO);
	exec_external_file_close(mcb);
	return (0);
}
