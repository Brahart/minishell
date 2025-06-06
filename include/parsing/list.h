/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asinsard <asinsard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:12:50 by asinsard          #+#    #+#             */
/*   Updated: 2025/04/10 17:01:41 by asinsard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include "token.h"

# define E_IO 5
# define MEM_ALLOC 12
# define IS_A_DIR 21

enum				e_type;
typedef enum e_type	t_type;

typedef struct s_token
{
	int				error;
	struct s_token	*next;
	struct s_token	*prev;
	struct s_token	*group;
	char			**content;
	char			*curr_dir;
	enum e_type		token;
	int				priority;
}	t_token;

/* ----------------------LIST---------------------- */
bool					add_back(t_token **head, char *str);
void					free_parse(t_token *list);

#endif
