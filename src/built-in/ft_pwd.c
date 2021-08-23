/*
 * 멘데토리에서 요구된 기능은 pwd 옵션없이의 명령이다.
 * 따라서, pwd 명령의 인자값은 다 무효로 한다.
 * 1. pwd 명령을 입력한다
 * 2. 현재 디렉토리의 값을 구한뒤 해당 값을 리턴한다.
 */

#include "../../minishell.h"

char *ft_pwd()
{
	char *current_path;

	current_path = NULL;
	return (current_path);	// 현재 디렉토리 경로 리턴
}