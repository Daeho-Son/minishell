/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dason <dason@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:03:08 by dason             #+#    #+#             */
/*   Updated: 2021/11/24 11:50:22 by dason            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

int	get_l_type(char *s)
{
	if (*s == '|')
		return (LTYPE_PIPE);
	else if (*s == '<' && *(s + 1) == '<')
		return (LTYPE_REDIRECT2_L);
	else if (*s == '>' && *(s + 1) == '>')
		return (LTYPE_REDIRECT2_R);
	else if (*s == '<')
		return (LTYPE_REDIRECT_L);
	else if (*s == '>')
		return (LTYPE_REDIRECT_R);
	else
		return (LTYPE_COMMAND);
}

bool	is_quote(char c)
{
	if (c == '\"')
		return (true);
	if (c == '\'')
		return (true);
	return (false);
}

bool	is_ltype_redirect(char c)
{
	if (c == LTYPE_REDIRECT_L)
		return (true);
	if (c == LTYPE_REDIRECT2_L)
		return (true);
	if (c == LTYPE_REDIRECT_R)
		return (true);
	if (c == LTYPE_REDIRECT2_R)
		return (true);
	return (false);
}

int	get_num_of_redirect(char *s)
{
	int		count;
	int		i;
	int		quote;

	count = 0;
	i = -1;
	while (++i < (int)ft_strlen(s))
	{
		if (get_l_type(&s[i]) == LTYPE_REDIRECT2_L || \
			get_l_type(&s[i]) == LTYPE_REDIRECT2_R)
		{
			i++;
			count++;
		}
		else if (get_l_type(&s[i]) != LTYPE_COMMAND)
			count++;
		if (is_quote(s[i]))
		{
			quote = s[i];
			while (s[++i])
				if (s[i] == quote && i++)
					break ;
		}
	}
	return (count);
}
