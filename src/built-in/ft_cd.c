/*
 * cd 명령은 단순히 타겟 경로에 이동하는 명령
 * 멘데토리 - 다른 옵션 X, 오직 상대경로/절대경로 이동
 *
 * chdir() 함수 자체가 상대경로도 인식해주기 때문에 따로 처리가 필요하지 않음
 */

#include "minishell.h"

// cd 명령어는 '무조건' 첫번째 인자값만 인식한다.
void	ft_cd(t_simple_cmd *simple_cmd, t_list *env, t_mcb *mcb)
{
	int	rtn;
	char *output;

	rtn = chdir( simple_cmd->argv[1] );	// 경로 이동
	output = ft_strjoin(ft_strdup(strerror(errno)), ft_strdup("\n"));
	if(rtn == -1)	// 에러 케이스
		write(2, output, ft_strlen(output) + 1);
	if(output)
		free(output);
	exit(0);
}
