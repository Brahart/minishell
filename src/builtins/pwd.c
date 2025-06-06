/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:33:43 by oelleaum          #+#    #+#             */
/*   Updated: 2025/05/26 18:02:06 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "env_utils.h"
#include "libft.h"
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>

int	builtin_pwd(t_var **env)
{
	char	buf[PATH_MAX];
	char	*s;

	s = NULL;
	if (getcwd(buf, sizeof(buf)) != NULL)
	{
		s = ft_strjoin(buf, "\n");
		if (errno == ENOMEM)
			return (errno);
		ft_putstr_fd(s, 1);
		free(s);
		return (0);
	}
	else
	{
		s = ft_strjoin(get_value(env, "PWD"), "\n");
		if (errno == ENOMEM)
			return (errno);
		if (s)
			ft_putstr_fd(s, 1);
		else
			perror("pwd");
		return (1);
	}
	return (0);
}
