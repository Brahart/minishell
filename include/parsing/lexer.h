/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asinsard <asinsard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 00:13:42 by asinsard          #+#    #+#             */
/*   Updated: 2025/05/27 00:56:10 by asinsard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdbool.h>

# define MEM_ALLOC 12

typedef struct s_lexer
{
	struct s_lexer	*next;
	struct s_lexer	*prev;
	char			*arg;
}	t_lexer;

/* ----------------------LEXER---------------------- */
bool					check_op_and_parenthesis(t_lexer *lexer);
bool					parse_line(char *str, t_lexer **list);
int						alloc_quote_to_lexer(char *str, char c, t_lexer **list);
int						alloc_space_to_lexer(char *str, t_lexer **list);
void					add_lexer_back(t_lexer **head, char *str);
void					alloc_operator_to_lexer(char *str, int i,
							t_lexer **list);
void					alloc_word_to_lexer(char *str, int *i, t_lexer **list);
void					free_lexer(t_lexer *head);

#endif