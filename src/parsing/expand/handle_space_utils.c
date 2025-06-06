/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_space_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asinsard <asinsard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:39:39 by asinsard          #+#    #+#             */
/*   Updated: 2025/06/05 00:10:23 by asinsard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "list.h"
#include "libft.h"
#include <stdlib.h>
#include <errno.h>

bool	verif_is_token_valid(t_type token)
{
	if (token == SPACE || token == O_AND || token == O_OR
		|| token == R_IN || token == HD || token == APPEND
		|| token == TRUNC || token == PIPE
		|| token == L_PARENTHESIS || token == R_PARENTHESIS)
		return (false);
	else
		return (true);
}

void	add_space(t_token **node)
{
	char	*res;
	int		len;

	len = ft_strlen((*node)->content[0]);
	if (!len || ((*node)->content[0][len - 1]
		&& (*node)->content[0][len - 1] == ' '))
		return ;
	res = ft_strjoin((*node)->content[0], " ");
	if (!res)
	{
		free_parse(*node);
		errno = MEM_ALLOC;
		return ;
	}
	free((*node)->content[0]);
	(*node)->content[0] = res;
}

static void	assign_content_without_space(char *str, char *res, int i, int j)
{
	int	is_word;

	is_word = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]))
		{
			if (is_word)
			{
				res[j++] = ' ';
				is_word = 0;
			}
			i++;
		}
		else
		{
			res[j++] = str[i++];
			is_word = 1;
		}
	}
	if (j > 0 && res[j - 1] == ' ')
		j--;
	res[j] = '\0';
}

void	delete_space_content(t_token **node)
{
	char	*res;

	res = ft_calloc(sizeof(char), ft_strlen((*node)->content[0]) + 1);
	if (!res)
	{
		free_parse(*node);
		errno = MEM_ALLOC;
		return ;
	}
	assign_content_without_space((*node)->content[0], res, 0, 0);
	free((*node)->content[0]);
	(*node)->content[0] = ft_strdup(res);
	if (!(*node)->content[0])
	{
		free_parse(*node);
		errno = MEM_ALLOC;
		return ;
	}
	free(res);
}

void	delete_node_pointer(t_token **node)
{
	t_token	*to_delete;

	to_delete = (*node)->next;
	if (to_delete->next)
	{
		(*node)->next = to_delete->next;
		to_delete->next->prev = *node;
	}
	else
		(*node)->next = NULL;
	to_delete->next = NULL;
	to_delete->prev = NULL;
	free_tab(to_delete->content);
	if (to_delete->curr_dir)
		free(to_delete->curr_dir);
	free(to_delete);
}
