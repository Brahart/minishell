
#include "libft.h"
#include "minishell.h"
#include <stdlib.h>

int	swap_nodes(t_var *n1, t_var *n2)
{
	char	*tmp_key;
	char	*tmp_value;
	int		tmp_env;
	int		tmp_exported;

	tmp_key = n1->key;
	tmp_value = n1->value;
	tmp_env = n1->env;
	tmp_exported = n1->exported;
	n1->key = n2->key;
	n1->value = n2->value;
	n1->env = n2->env;
	n1->exported = n2->exported;
	n2->key = tmp_key;
	n2->value = tmp_value;
	n2->env = tmp_env;
	n2->exported = tmp_exported;
	return (0);
}

int	sort_list(t_var **l)
{
	t_var	*tmp;
	int		sorted;

	sorted = 0;
	tmp = *l;
	if (!tmp)
		return (1);
	while (sorted == 0)
	{
		sorted = 1;
		tmp = *l;
		while (tmp->next)
		{
			if (compare_keys(tmp->key, tmp->next->key) > 0)
			{
				sorted = 0;
				swap_nodes(tmp, tmp->next);
			}
			tmp = tmp->next;
		}
	}
	return (0);
}

t_var	*copy_list(t_var **env)
{
	t_var	*tmp;
	t_var	*last;
	t_var	*new_node;
	t_var	*copy;

	tmp = *env;
	last = NULL;
	copy = NULL;
	while (tmp)
	{
		new_node = malloc(sizeof(t_var));
		if (!new_node)
			exit(1); // a mieux protegetr
		new_node->key = ft_strdup(tmp->key);
		new_node->value = ft_strdup(tmp->value);
		new_node->next = NULL;
		if (last)
			last->next = new_node;
		else
			copy = new_node;
		last = new_node;
		tmp = tmp->next;
	}
	return (copy);
}

int	array_size(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}
