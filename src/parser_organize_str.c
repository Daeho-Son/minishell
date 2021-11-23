/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_organize_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dason <dason@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 09:41:36 by dason             #+#    #+#             */
/*   Updated: 2021/11/17 15:48:32 by dason            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

static char	*str_recomb_single(char **split, int len, int count_c, char c)
{
	char	*new_str;
	int		str_i;
	int		j;

	new_str = (char *)ft_calloc(len + count_c * 3 + 1, sizeof(char));
	if (!new_str)
		exit(1);
	str_i = -1;
	while (*split)
	{
		j = -1;
		while ((*split)[++j])
			new_str[++str_i] = (*split)[j];
		if (count_c--)
		{
			new_str[++str_i] = ' ';
			new_str[++str_i] = c;
			new_str[++str_i] = ' ';
		}
		split++;
	}
	return (new_str);
}

static char	*str_recomb_double(char **split, int len, int count_c, char c)
{
	char	*new_str;
	int		str_i;
	int		j;

	new_str = (char *)ft_calloc(len + count_c * 3 + 2, sizeof(char));
	if (!new_str)
		exit(1);
	str_i = -1;
	while (*split)
	{
		j = -1;
		while ((*split)[++j])
			new_str[++str_i] = (*split)[j];
		if (count_c--)
		{
			new_str[++str_i] = ' ';
			new_str[++str_i] = c;
			new_str[++str_i] = c;
			new_str[++str_i] = ' ';
		}
		split++;
	}
	return (new_str);
}

static int	str_split(char ***split, char *str, char c)
{
	char	*trim;
	int		len;
	int		i;

	*split = ft_split(str, c);
	if (!*split)
		exit(1);
	len = 0;
	i = -1;
	while ((*split)[++i])
	{
		trim = ft_strtrim((*split)[i], " ");
		if (!trim)
			exit(1);
		free((*split)[i]);
		(*split)[i] = trim;
		len += ft_strlen((*split)[i]);
	}
	return (len);
}

static char	*str_split_recomb(char *str, char c, bool double_redirect)
{
	char	*new_str;
	char	**split;
	int		len;

	if (!str)
		exit(1);
	len = str_split(&split, str, c);
	if (!double_redirect)
		new_str = str_recomb_single(split, len, get_num_of_c(str, c), c);
	else
		new_str = str_recomb_double(split, len, get_num_of_c(str, c) / 2, c);
	free_double_pointer(&split);
	free(str);
	return (new_str);
}

char	*organize_input_str(char *str)
{
	char	*new_str;

	if (ft_strchr(str, '|'))
		str = str_split_recomb(str, '|', false);
	if (ft_strchr(str, ';'))
		str = str_split_recomb(str, ';', false);
	if (ft_strchr(str, '<'))
	{
		if (*(ft_strchr(str, '<') + 1) != '<')
			str = str_split_recomb(str, '<', false);
		else
			str = str_split_recomb(str, '<', true);
	}
	if (ft_strchr(str, '>'))
	{
		if (*(ft_strchr(str, '>') + 1) != '>')
			str = str_split_recomb(str, '>', false);
		else
			str = str_split_recomb(str, '>', true);
	}
	new_str = ft_strtrim(str, " ");
	if (!new_str)
		exit(1);
	free(str);
	return (new_str);
}