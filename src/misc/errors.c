/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asinsard <asinsard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:27:24 by oelleaum          #+#    #+#             */
/*   Updated: 2025/05/29 18:25:01 by asinsard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
#include "libft.h"
#include <errno.h>
#include <stdlib.h>

int	malloc_error_cmd(char *to_free)
{
	int	saved_errno;

	saved_errno = errno;
	free(to_free);
	errno = saved_errno;
	return (errno);
}

int	error_cmd_dot_case(char *cmd)
{
	if (!ft_strncmp(cmd, ".", 2) && ft_strlen(cmd) == 1)
	{
		ft_putstr_fd("minishell: .: filename argument required\n.: \
			usage: . filename [arguments]\n",
			2);
		return (2);
	}
	return (0);
}

int	error_cmd_perm_not_found(char *cmd, int error_code)
{
	char	*s;
	char	*tmp;

	s = ft_strjoin("minishell: ", cmd);
	if (errno == ENOMEM)
		return (errno);
	tmp = s;
	if (error_code == 126)
		s = ft_strjoin(s, ": Permission denied\n");
	if (error_code == 127)
		s = ft_strjoin(s, ": command not found\n");
	if (errno == ENOMEM)
	{
		free(tmp);
		return (malloc_error_cmd(tmp));
	}
	free(tmp);
	ft_putstr_fd(s, 2);
	free(s);
	if (error_code == 126)
		return (126);
	return (127);
}

int	error_cmd(char *cmd, int error_code)
{
	if (error_cmd_dot_case(cmd) == 2)
		return (2);
	if (error_code == 21)
		return (error_cmd_is_a_directory(cmd));
	return (error_cmd_perm_not_found(cmd, error_code));
}
