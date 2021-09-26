/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjung <mjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 05:57:51 by ychoi             #+#    #+#             */
/*   Updated: 2021/09/27 08:29:30 by mjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_analysis(const t_token_info tokens, t_ast **root)
{
	int	idx;

	idx = syntax_pipeline_check(tokens, 0);
	if (idx == -1)
	{
		g_global.rtn = 258;
		printf("fail to syntax analysis\n");
		return (-1);
	}
	syntax_pipeline(tokens, 0, root);
	return (0);
}
