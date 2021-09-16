
#include "minishell.h"

int	exec_external(t_simple_cmd *simple_cmd, t_list *env)
{
	extern char **environ;
	pid_t pid, wpid;
	int status;

	pid = fork();	// 새로운 자식 프로세스 생성
	if (pid == 0)	// 자식 프로세스
	{
		// execve -> 바이너리 교체 : 새로운 프로세스로 실행
		if (execve(simple_cmd->file_path, simple_cmd->argv, environ) == -1)	// 바이너리 교체 실패
			ft_putendl_fd("ERROR", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)	// 부모 프로세스
	{
		do
		{	// 부모프로세스는 자식프로세스가 종료될때 까지 기다린다
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	else
	{
		ft_putendl_fd("ERROR", STDERR_FILENO);
	}
	return (0);
}
