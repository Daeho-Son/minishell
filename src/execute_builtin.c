/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dason <dason@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:31:26 by jongpark          #+#    #+#             */
/*   Updated: 2021/12/13 20:02:52 by dason            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_builtin(t_list *list)
{
	if (ft_strncmp(list->start_node->data, "env", 4) == 0 || \
	ft_strncmp(list->start_node->data, "export", 7) == 0 || \
	ft_strncmp(list->start_node->data, "unset", 6) == 0 || \
	ft_strncmp(list->start_node->data, "pwd", 4) == 0 || \
	ft_strncmp(list->start_node->data, "cd", 3) == 0 || \
	ft_strncmp(list->start_node->data, "echo", 5) == 0 || \
	ft_strncmp(list->start_node->data, "exit", 5) == 0)
		return (true);
	return (false);
}

void	exec_builtin(t_list *list, t_info *info)
{
	if (ft_strncmp(list->start_node->data, "env", 4) == 0)
		env(info);
	else if (ft_strncmp(list->start_node->data, "export", 7) == 0)
		ft_export(list, info);
	else if (ft_strncmp(list->start_node->data, "unset", 6) == 0)
		unset(list, info);
	else if (ft_strncmp(list->start_node->data, "pwd", 4) == 0)
		pwd();
	else if (ft_strncmp(list->start_node->data, "cd", 3) == 0)
		cd(list, info);
	else if (ft_strncmp(list->start_node->data, "echo", 5) == 0)
		echo(list);
	else if (ft_strncmp(list->start_node->data, "exit", 5) == 0)
	{
		printf("exit\n");
		exit(2);
	}
}

int	try_exec_builtin(t_list *list, t_info *info)
{
	if (is_builtin(list) == false)
		return (-1);
	preprocess(list, info);
	exec_builtin(list, info);
	postprocess_builtin(list, info);
	return (0);
}
