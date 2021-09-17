/*
 * 1. 특수변수 예외처리
 * 2. 전체 문자가 허용가능한 문자들로만 이루어졌는지 체크
 * 3. 첫번째 문자가 허용가능한 문자들로만 이루어 졌는지 체크
 * 4. 환경변수 key가 등록되어있지 않은 경우
 */

#include "minishell.h"

// 첫번째 글자 (영어, 밑줄)
int	allowed_character(char *string)
{
	int idx;

	idx = -1;
	if ('0' <= string[0] && string[0] <= '9')
		return (0);
	while (string[++idx])
	{
		if (!(('a' <= string[idx] && string[idx] <= 'z')
			|| ('A' <= string[idx] && string[idx] <= 'Z')
			|| ('0' <= string[idx] && string[idx] <= '9')
			|| '_' == string[idx]))
		{
			return(0);
		}
	}
	return (1);
}

int	check_env_key(char *key)
{
	// 특수변수 예외처리
	if (ft_strcmp(key, "$?") == 0)
		return (1);

	// 전체 key가 허용가능한 문자들로만 이루어졌는지 체크
	// 특수문자인 경우 (화이트리스트로 작성) 예외처리
	if (allowed_character(key))
		return (0);

	return (1);
}
