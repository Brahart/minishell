/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asinsard <asinsard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 21:07:56 by asinsard          #+#    #+#             */
/*   Updated: 2025/04/14 16:09:48 by asinsard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

# include "list.h"

struct					s_token;
typedef struct s_token	t_token;

typedef struct s_tree
{
	struct s_tree	*left;
	struct s_tree	*right;
	t_token			*content;
	int				priority;
}	t_tree;

void	add_to_root(t_token *node, t_tree **root);
void	free_tree(t_tree *head);

t_token	*find_best_priority(t_token *start, t_token *end);
void	last_node(t_token **node);
void	assign_priority(t_token **head);

#endif