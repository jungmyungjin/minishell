/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjung <mjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 07:54:01 by mjung             #+#    #+#             */
/*   Updated: 2021/09/27 08:02:34 by mjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*parser(t_list *env, char *line)
{
	t_token_info	tokens;
	t_ast			*root;
	int				result;

	result = lexical_analysis(env, line, &tokens);
	if (result == -1)
		return (NULL);
	root = NULL;
	result = syntax_analysis(tokens, &root);
	if (result == -1 || root == NULL)
	{
		free_tokens(&tokens);
		return (NULL);
	}
	set_full_path_in_tree(env, root);
	free_tokens(&tokens);
	return (root);
}

void	init_mcb(t_mcb *mcb)
{
	mcb->next_pipe_check = 0;
	mcb->pre_pipe_check = 0;
	mcb->pipe_read_end = STDIN_FILENO;
	mcb->pipe_write_end = STDOUT_FILENO;
	mcb->fd_input = STDIN_FILENO;
	mcb->fd_output = STDOUT_FILENO;
}

void	minishell_loop(t_list **env)
{
	char	*line;
	t_ast	*root;
	t_mcb	mcb;

	set_signal();
	while (1)
	{
		line = readline(">> ");
		if (line == NULL)
			sig_exit_shell();
		root = parser(*env, line);
		if (root != NULL)
		{
			init_mcb(&mcb);
			search_tree(root, *env, &mcb);
			free_tree(&root);
		}
		if (ft_strcmp(line, ""))
			add_history(line);
		free(line);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_list	*env;

	if (argc || argv)
		;
	env_initialize(&env, envp);
	minishell_loop(&env);
	return (EXIT_SUCCESS);
}
