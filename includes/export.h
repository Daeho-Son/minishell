/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun <hyun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 09:29:20 by hyun              #+#    #+#             */
/*   Updated: 2021/11/11 09:29:48 by hyun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_H
# define EXPORT_H

# include "list_node.h"
# include "info.h"
# include "envp.h"
# include "../libft/includes/libft.h"
# include <stdbool.h>

int	export(t_list *list, t_info *info);
int	remove_envp_index(int idx, char **envp, t_info *info);
int	remove_envp(char *data, char **envp, t_info *info);

#endif
