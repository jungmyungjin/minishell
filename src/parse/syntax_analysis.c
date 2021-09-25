
#include "minishell.h"

int syntax_analysis(const t_token_info tokens, t_ast **root)
{
    int idx;

    idx = syntax_pipeline_check(tokens, 0);
    if (idx == -1)
    {
    	global.rtn = 258;
        printf("fail to syntax analysis\n");
        return (-1);
    }
    syntax_pipeline(tokens, 0, root);
    return (0);
}
