/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asinsard <asinsard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:04:05 by oelleaum          #+#    #+#             */
/*   Updated: 2025/05/27 17:42:00 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "libft.h"
#include "structs.h"
#include <errno.h>
#include <stdlib.h>

int	set_node(t_var **node, int mode)
{
	(*node)->env = 0;
	(*node)->exported = 0;
	(*node)->loaded = 0;
	if (mode == 1)
	{
		(*node)->env = 1;
	}
	else if (mode == 2)
	{
		(*node)->exported = 1;
	}
	else if (mode == 3)
	{
		(*node)->env = 1;
		(*node)->exported = 1;
	}
	else if (mode == 4)
	{
		(*node)->loaded = 1;
	}
	return (0);
}

int	add_first_node(t_var **lst, t_var **new, char *s, int mode)
{
	char	**key_value;

	(*new)->key = NULL;
	(*new)->value = NULL;
	key_value = ft_split(s, '=');
	if (!key_value)
		return (free_node_var(*new, NULL));
	(*new)->key = ft_strdup(key_value[0]);
	if (errno == ENOMEM)
		return (free_node_var(*new, key_value));
	if (key_value[1])
	{
		(*new)->value = ft_strdup(key_value[1]);
		if (errno == ENOMEM)
			return (free_node_var(*new, key_value));
	}
	free_array(key_value);
	*lst = *new;
	(*new)->next = NULL;
	return (set_node(new, mode));
}

char	**ft_split_on_first_equal(char *s)
{
	char	**splitted;
	char	*equal_ptr;

	splitted = malloc(3 * sizeof(char *));
	if (!splitted)
		return (NULL);
	splitted[0] = NULL;
	splitted[1] = NULL;
	splitted[2] = NULL;
	equal_ptr = ft_strchr(s, '=');
	if (!equal_ptr)
	{
		splitted[0] = ft_strdup(s);
		return (splitted);
	}
	splitted[0] = ft_strndup(s, equal_ptr - s);
	if (*(equal_ptr + 1))
		splitted[1] = ft_strdup(equal_ptr + 1);
	else
		splitted[1] = ft_strdup("");
	return (splitted);
}

int	build_minimal_env(t_var **env, char *arg)
{
	char	*s;

	s = NULL;
	if (get_cwd_init(s) == -1)
		return (-1);
	if (!s)
		return (-1);
	s = ft_strjoin("PWD=", s);
	if (!s)
		return (malloc_free_string(s));
	if (add_back_var(env, s, 3) == -1)
		return (malloc_free_string(s));
	free(s);
	if (add_default_shell_vars(env) == -1)
		return (-1);
	if (init_last_cmd_var(arg, env) == -1)
		return (-1);
	return (add_back_var(env, "_=env", 0));
}
