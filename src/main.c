#include "../minishell.h"

// tree 형태로 파싱
char *parser(t_list *env, char *line)
{
    char **tokens;

    // 토큰화 ["ls", "-al", "|", "cat"]
    tokens = tokenizer(env, line);
    if (tokens == NULL) // 토큰화 실패.
        return (NULL);

    // token 에 의미(type) 부여
    // lexer = lexical_analysis(tokens);

    // 문법 체크 및 tree 로
    // btree = syntactic_analysis();

    return NULL;
}


void minishell_loop(t_list **env)
{
	char *line;

	while (1){
		line = readline(">> ");
		parser(*env, line); // 파서 시작.
		// macos 에서 해당 함수를 사용하기위해 make 설정을 해야함.
		rl_replace_line("", 0);
		add_history(line);
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
