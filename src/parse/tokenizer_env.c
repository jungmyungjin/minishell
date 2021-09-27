/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 07:45:13 by mjung             #+#    #+#             */
/*   Updated: 2021/09/27 14:20:11 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_token_in_env(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (is_env(str, i))
			return (i);
		i++;
	}
	return (-1);
}

int	find_dollar_end(char *str, int j)
{
	if (str[j] == '?')
		return (j);
	while (is_env_character(str[j]))
		j++;
	return (j - 1);
}

void	set_new_str(
	char *new_str, char *substr1, char *env_value, char *substr2)
{
	char	*sub_ptr1;
	char	*sub_ptr2;

	sub_ptr1 = substr1;
	sub_ptr2 = substr2;
	while (*substr1 != '\0')
		*(new_str++) = *(substr1++);
	while (*env_value != '\0')
		*(new_str++) = *(env_value++);
	while (*substr2 != '\0')
		*(new_str++) = *(substr2++);
	*new_str = '\0';
	free(sub_ptr1);
	free(sub_ptr2);
}

char	*create_new_str(
	t_list *env, char *token, int start_dollar, int end_dollar)
{
	char	*env_value;
	char	*env_key;
	char	*new_str;
	int		new_str_len;

	env_key = ft_substr(token, start_dollar + 1, end_dollar - start_dollar);
	if (ft_strcmp(env_key, "?") == 0)
		env_value = ft_itoa(g_global.rtn);
	else
		env_value = get_env_value(env, env_key);
	new_str_len = ft_strlen(token)
		- (end_dollar - start_dollar + 1) + ft_strlen(env_value);
	new_str = (char *)malloc(sizeof(char) * (new_str_len + 1));
	if (new_str == NULL)
		allocation_error();
	set_new_str(new_str, ft_substr(token, 0, start_dollar), env_value,
		ft_substr(token, end_dollar + 1, ft_strlen(token)));
	free(env_key);
	free(env_value);
	return (new_str);
}

void	convert_env(t_list *env, t_token_info *token_info)
{
	int		i;
	int		end_dollar;
	int		start_dollar;
	char	*new_str;

	i = 0;
	while (i < token_info->count)
	{
		if (token_info->tokens[i].type != T_SINGLE_QUOTES)
		{
			start_dollar = is_token_in_env(token_info->tokens[i].str);
			if (start_dollar != -1)
			{
				end_dollar = find_dollar_end(
						token_info->tokens[i].str, start_dollar + 1);
				new_str = create_new_str(env,
						token_info->tokens[i].str, start_dollar, end_dollar);
				free(token_info->tokens[i].str);
				token_info->tokens[i].str = new_str;
				continue ;
			}
		}
		i++;
	}
}
