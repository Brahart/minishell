/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asinsard <asinsard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 00:33:04 by asinsard          #+#    #+#             */
/*   Updated: 2025/06/04 17:10:47 by asinsard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"
#include "lexer.h"
#include "token.h"
#include "list.h"
#include "libft.h"
#include "tree.h"
#include "quote.h"
#include <stdlib.h>
#include <errno.h>

static char	*create_new_line(t_token *head)
{
	int		len;
	char	*line;
	int		pos;

	len = find_len_for_new_line(head);
	line = ft_calloc(sizeof(char), len + 1);
	if (!line)
		return (NULL);
	pos = 0;
	while (head)
	{
		if (head->token == EXPAND || head->token == WILDCARD)
			case_is_expand(head, &pos, &line);
		else
		{
			len = ft_strlen(head->content[0]);
			ft_memcpy(&line[pos], head->content[0], len);
			pos += len;
			line[pos] = ' ';
		}
		head = head->next;
	}
	line[pos] = '\0';
	return (line);
}

bool	case_is_wildcard_and_reparse(t_token **head, bool flag, t_var *list_env)
{
	if (!handle_wildcard(head, flag))
		return (false);
	if (!parse_again(head, list_env, &flag))
	{
		free_parse(*head, NULL, MEM_ALLOC);
		errno = MEM_ALLOC;
		return (false);
	}
	return (true);
}

bool	parse_again(t_token **head, t_var *list_env, bool *flag)
{
	char	*line;

	line = create_new_line(*head);
	if (!line)
		return (false);
	free_parse(*head, NULL, MEM_ALLOC);
	*head = NULL;
	if (!lexing_and_tokenize(line, head, list_env, flag)
		|| !error_one_quote(head))
	{
		free(line);
		return (false);
	}
	free(line);
	if (!error_one_parenthesis(head))
	{
		errno = MEM_ALLOC;
		return (false);
	}
	return (true);
}
