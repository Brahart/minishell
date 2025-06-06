/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asinsard <asinsard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:04:26 by asinsard          #+#    #+#             */
/*   Updated: 2025/06/04 23:29:38 by asinsard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include <stdbool.h>

# define INFIX 1
# define PREFIX 2
# define SUFFIX 3
# define JOKER 4

struct					s_token;
typedef struct s_token	t_token;

/* ----------------------WILDCARD---------------------- */
bool					is_wildcard(char *str);
bool					handle_current_dir(int *i, char ***res);
bool					handle_wildcard(t_token **head, bool flag);
void					assign_wildcard(t_token **node, char **res, int count);
void					verif_wildcard(t_token **head);

/* -------------------WILDCARD UTILS------------------- */
bool					find_prefix(char *str, char *src);
bool					find_suffix(char *str, char *src);
char					**extract_current_dir(void);
int						compare_content(char *s1, char *s2);
int						which_case_of_wildcard(char *str);
void					add_space_for_wildcard(t_token **node);
void					is_infix(t_token **node, char **current_dir);
void					is_joker(t_token **node, char **current_dir);
void					is_prefix(t_token **node, char **current_dir);
void					is_suffix(t_token **node, char **current_dir);
void					sort_wildcard_arg(char **array);

#endif