/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asinsard <asinsard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:03:14 by asinsard          #+#    #+#             */
/*   Updated: 2025/06/04 17:05:13 by asinsard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "list.h"
#include "libft.h"

int	find_len_for_new_line(t_token *head)
{
	int		j;
	int		len;

	len = 0;
	while (head)
	{
		j = 0;
		while (head->content[0][j])
			j++;
		len += j + 1;
		if (head->token == EXPAND)
			len += 2;
		head = head->next;
	}
	return (len);
}


static void	copy_expand(t_token *node, char **line, int *pos, int i)
{
	int		len;
	bool	flag;

	len = ft_strlen(&node->content[0][i]);
	flag = false;
	if (node->content[0][i] && node->content[0][i] == ' ')
	{
		(*line)[*pos] = ' ';
		(*pos)++;
		i++;
		flag = true;
	}
	(*line)[*pos] = '"';
	(*pos)++;
	ft_memcpy(&(*line)[*pos], &node->content[0][i], len);
	if (flag)
		*pos += len - 1;
	else
		*pos += len;
	(*line)[*pos] = '"';
	(*pos)++;
	(*line)[*pos] = ' ';
}

void	case_is_expand(t_token *node, int *pos, char **line)
{
	int		i;
	bool	flag;

	i = 0;
	flag = false;
	if (node->error != LITERAL_EXPAND)
	{
		i = ft_countword(node->content[0]);
		if (i > 1)
		{
			flag = true;
			i = 0;
			while (node->content[0][i] && !ft_isspace(node->content[0][i]))
			{
				(*line)[*pos] = node->content[0][i];
				i++;
				(*pos)++;
			}
		}
	}
	if (!flag)
		i = 0;
	copy_expand(node, line, pos, i);
}
