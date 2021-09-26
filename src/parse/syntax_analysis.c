/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 05:57:51 by ychoi             #+#    #+#             */
/*   Updated: 2021/09/27 05:59:21 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_analysis(const t_token_info tokens, t_ast **root)
{
	int	idx;

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
