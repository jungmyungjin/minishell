#include "minishell.h"


void sig_new_line(int status)
{
    if (global.child == 0)
    {
        printf("\n");
        rl_on_new_line(); // 새로운 라인 만들기
        rl_replace_line("", 0); // 기존 라인을 지움.
        rl_redisplay();
    }
    else
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
    }
	global.rtn = 130;
}

void sig_exit_shell()
{
    printf("bye\n");
    exit(EXIT_SUCCESS);
}

void set_signal()
{
    signal(SIGINT, sig_new_line); // ctrl + c
    signal(SIGQUIT, SIG_IGN); // ctrl + '\'
}
