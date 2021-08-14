#include "minishell.h"


void minishell_loop()
{
	char *line;

	while (1){
		line = readline(">> ");

		// macos 에서 해당 함수를 사용하기위해 make 설정을 해야함.
		// rl_replace_line("", 0);

		add_history(line);
		free(line);
	}
}


int main(int argc, char *argv[], char *envp[])
{
	minishell_loop();
	return (EXIT_SUCCESS);
}
