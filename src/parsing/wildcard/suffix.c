/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suffix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asinsard <asinsard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 02:28:30 by asinsard          #+#    #+#             */
/*   Updated: 2025/06/03 21:35:49 by asinsard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "token.h"
#include "libft.h"
#include "list.h"
#include <errno.h>
#include <stdlib.h>

static void	alloc_suffix(t_token **node, char **current_dir, char **res)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (current_dir[i])
	{
		if (find_suffix(current_dir[i], &(*node)->content[0][1]))
		{
			res[count] = ft_strdup(current_dir[i]);
			if (!res[count])
			{
				errno = MEM_ALLOC;
				free_tab(res);
				return ;
			}
			count++;
		}
		i++;
	}
	assign_wildcard(node, res, count);
}

bool	find_suffix(char *str, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!src[j])
		return (false);
	while (str[i])
	{
		while (i + j > 0 && str[i + j] == src[j]
			&& src[j])
		{
			j++;
			if (!src[j] || src[j] == '*')
				return (true);
		}
		j = 0;
		i++;
	}
	return (false);
}

void	is_suffix(t_token **node, char **current_dir)
{
	int		i;
	int		count;
	char	**res;

	i = 0;
	count = 0;
	while (current_dir[i])
	{
		if (find_suffix(current_dir[i], &(*node)->content[0][1]))
			count++;
		i++;
	}
	res = malloc(sizeof(char *) * (count + 1));
	if (!res)
	{
		errno = MEM_ALLOC;
		return ;
	}
	alloc_suffix(node, current_dir, res);
}
