#include "../minishell.h"

// tree 형태로 파싱
t_ast *parser(t_list *env, char *line)
{
    t_token_info tokens;
    t_ast *root;
    int result;

    result = lexical_analysis(env, line, &tokens);
    if (result == -1) // 토큰화 실패.
        return (NULL);

    for (int i = 0; i<=tokens.count; i++)
        printf("index: %d, str: %s, type: %d\n", i, tokens.tokens[i].str, tokens.tokens[i].type);

    // 문법 체크 및 tree 로
    root = NULL;
    result = syntax_analysis(tokens, &root);
    if (result == -1 || root == NULL) // 문법 체크 실패
    {
        free_tokens(&tokens);
        return (NULL);
    }
    free_tokens(&tokens);
    return root;
}


void minishell_loop(t_list **env)
{
	char *line;
	t_ast *root;

	while (1){
		line = readline(">> ");
		root = parser(*env, line); // 파서 시작.
		if (root != NULL)
		{
		    search_tree(root, *env);
		    free_tree(&root);
		}
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
