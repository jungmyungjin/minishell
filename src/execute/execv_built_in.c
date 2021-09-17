#include "minishell.h"

void execve_built_in(t_simple_cmd *simple_cmd, t_list *env)
{
    // cd
    // env
    // export
    // unset;

//	if (!ft_strcmp(simple_cmd->original, "cd"))
//		ft_cd(simple_cmd, env);
	if (!ft_strcmp(simple_cmd->original, "env"))
		ft_env(simple_cmd, env);
	if (!ft_strcmp(simple_cmd->original, "export"))
		ft_export(simple_cmd, env);
	if (!ft_strcmp(simple_cmd->original, "unset"))
		ft_unset(simple_cmd, env);
//	if (!ft_strcmp(simple_cmd->original, "pwd"))
//		ft_pwd(simple_cmd, env);
}
