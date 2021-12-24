/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handling_exception.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dason <dason@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 09:44:28 by dason             #+#    #+#             */
/*   Updated: 2021/12/24 14:20:11 by dason            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

static bool	check_parse_error_near(t_list *list)
{
	int		l_type;

	if (list && list->next && \
		list->l_type != LTYPE_COMMAND && \
		list->l_type != LTYPE_FILE && \
		list->next->l_type != LTYPE_COMMAND && \
		list->next->l_type != LTYPE_FILE)
	{
		l_type = list->next->l_type;
		if (l_type == 2)
			printf("minishell: syntax error near unexpected token `|'\n");
		if (l_type == 3)
			printf("minishell: syntax error near unexpected token `<'\n");
		if (l_type == 4)
			printf("minishell: syntax error near unexpected token `<<'\n");
		if (l_type == 5)
			printf("minishell: syntax error near unexpected token `>'\n");
		if (l_type == 6)
			printf("minishell: syntax error near unexpected token `>>'\n");
		return (false);
	}
	return (true);
}

static bool	check_non_path_and_non_eof(t_list *list)
{
	while (list)
	{
		if (list->l_type != LTYPE_COMMAND && \
			list->l_type != LTYPE_FILE && \
			(!list->next || \
			list->next->l_type != LTYPE_FILE))
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return (false);
		}
		list = list->next;
	}
	return (true);
}

int	parser_handling_exception(t_list *list)
{
	t_list		*work_list;

	while (list)
	{
		work_list = list;
		if (check_parse_error_near(work_list) == false)
			return (0);
		if (check_non_path_and_non_eof(work_list) == false)
			return (0);
		list = list->next;
	}
	return (1);
}
