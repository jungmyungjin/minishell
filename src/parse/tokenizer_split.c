/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 06:09:33 by ychoi             #+#    #+#             */
/*   Updated: 2021/09/27 15:28:45 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_single_quotes(const char *line, int i)
{
	while (line[i] != '\0' && line[i] != '\'')
	{
		if (line[i] == '\\' && line[i + 1] == '\'')
			i++;
		i++;
	}
	if (line[i] == '\0')
		return (-1);
	return (i);
}

int	find_double_quotes(const char *line, int i)
{
	while (line[i] != '\0' && line[i] != '\"')
	{
		if (line[i] == '\\' && line[i + 1] == '\"')
			i++;
		i++;
	}
	if (line[i] == '\0')
		return (-1);
	return (i);
}

int	find_quotes_to_end(const char *line, int i, t_token *token)
{
	if (line[i + 1] == '\0')
		return (-1);
	if (line[i] == '\"')
	{
		i++;
		i = find_double_quotes(line, i);
		if (i == -1)
			return (-1);
		if (token != NULL)
			token->type = T_DOUBLE_QUOTES;
	}
	else if (line[i] == '\'')
	{
		i++;
		i = find_single_quotes(line, i);
		if (i == -1)
			return (-1);
		if (token != NULL)
			token->type = T_SINGLE_QUOTES;
	}
	return (i);
}

int	is_space(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

int	tokenizer_split(char *line, t_token_info *token_info)
{
	if (*line == '\0')
		return (-1);
	token_info->count = counting_tokens(line);
	if (token_info->count <= 0)
		return (-1);
	token_info->tokens = (t_token *)malloc(sizeof(t_token)
			* (token_info->count + 1));
	if (token_info->tokens == NULL)
		allocation_error();
	token_info->tokens = split_line(line,
			token_info->tokens, token_info->count);
	return (0);
}
