/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 07:48:39 by mjung             #+#    #+#             */
/*   Updated: 2021/09/27 15:29:07 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexical_analysis(t_list *env, char *line, t_token_info *token_info)
{
	int	result;

	result = tokenizer_split(line, token_info);
	if (result == -1)
	{
		g_global.rtn = 258;
		printf("fail to lexical analysis\n");
		return (-1);
	}
	convert_env(env, token_info);
	set_tokenizer_type(token_info);
	return (0);
}

void	free_tokens(t_token_info *token_info)
{
	int	i;

	i = 0;
	while (i < token_info->count)
	{
		free(token_info->tokens[i].str);
		i++;
	}
	free(token_info->tokens);
}
