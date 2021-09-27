/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_split2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjung <mjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 06:09:33 by ychoi             #+#    #+#             */
/*   Updated: 2021/09/27 08:54:12 by mjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	counting_tokens_while(char *line, int *i, int *count)
{
	if (is_space(line[*i]))
		(*i)++;
	else if (line[*i] == '\"' || line[*i] == '\'')
	{
		*i = find_quotes_to_end(line, *i, NULL);
		if (*i == -1)
			return ;
		(*i)++;
		(*count)++;
	}
	else
	{
		while (line[*i] != '\0' && !is_space(line[*i]))
		{
			if (line[*i] == '\"' || line[*i] == '\'')
				break ;
			(*i)++;
		}
		(*count)++;
	}
}

int	counting_tokens(char *line)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (line[i] != '\0')
	{
		counting_tokens_while(line, &i, &count);
		if (i == 1)
			return (-1);
	}
	return (count);
}

void	split_line_while(int *i, const char *line, t_token *tokens, int *row)
{
	int	start;

	if (is_space(line[*i]))
		(*i)++;
	else if (line[*i] == '\"' || line[*i] == '\'')
	{
		start = *i;
		*i = find_quotes_to_end(line, *i, &tokens[*row]);
		tokens[(*row)++].str = ft_substr(line, start + 1, *i - start - 1);
		(*i)++;
	}
	else
	{
		start = *i;
		while (line[*i] != '\0' && !is_space(line[*i]))
		{
			if (line[*i] == '\"' || line[*i] == '\'')
				break ;
			(*i)++;
		}
		tokens[(*row)++].str = ft_substr(line, start, *i - start);
	}
}

t_token	*split_line(const char *line, t_token *tokens, int count)
{
	int	i;
	int	row;

	i = 0;
	row = 0;
	while (line[i] != '\0' && row < count)
		split_line_while(&i, line, tokens, &row);
	tokens[row].str = NULL;
	return (tokens);
}
