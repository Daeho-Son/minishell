/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_make_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dason <dason@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:58:45 by dason             #+#    #+#             */
/*   Updated: 2021/12/23 20:45:35 by dason            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

static void	process_when_quote(char *s, int *i, int *len)
{
	int		quote;

	quote = s[*i + *len];
	(*len)++;
	while (s[*i + *len] && s[*i + *len] != quote)
		(*len)++;
}

static void	process_the_list(t_list **list, char *s, int *i, int *len)
{
	t_list	*new_list;
	char	*sub_str;

	while (s[*i + *len] && get_ltype(&s[*i + *len]) == LTYPE_COMMAND)
	{
		if (s[*i + *len] == '\"' || s[*i + *len] == '\'')
			process_when_quote(s, i, len);
		(*len)++;
	}
	sub_str = ft_substr(s, *i, *len);
	if (s[*i - 2] == '<' || s[*i - 2] == '>')
		new_list = ft_create_list(LTYPE_FILE, \
				ft_create_node(NTYPE_COMMAND, ft_strtrim(sub_str, " ")));
	else
		new_list = ft_create_list(LTYPE_COMMAND, \
				ft_create_node(NTYPE_COMMAND, ft_strtrim(sub_str, " ")));
	if (*i == 0)
		*list = new_list;
	else
		ft_lstadd_back(*list, new_list);
	free(sub_str);
}

void	make_list(t_list **list, char *s)
{
	int		i;
	int		len;

	i = 0;
	while (i < (int)ft_strlen(s))
	{
		while (s[i] == ' ')
			i++;
		if (i == 0 || get_ltype(&s[i]) == LTYPE_COMMAND)
		{
			len = 0;
			process_the_list(list, s, &i, &len);
			i += len;
		}
		else if (get_ltype(&s[i]) != LTYPE_COMMAND)
		{
			ft_lstadd_back(*list, ft_create_list(get_ltype(&s[i]), NULL));
			if (get_ltype(&s[i]) == LTYPE_REDIRECT_L2 || \
				get_ltype(&s[i]) == LTYPE_REDIRECT_R2)
				i += 2;
			else
				i += 1;
		}
	}
}