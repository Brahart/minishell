/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:33:31 by oelleaum          #+#    #+#             */
/*   Updated: 2025/05/26 18:39:56 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"
#include <unistd.h>

int	wait_children(pid_t last_child)
{
	int		status;
	int		last_status;
	pid_t	pid;

	last_status = 0;
	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		if (pid == last_child)
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				last_status = 128 + WTERMSIG(status);
				if (WTERMSIG(status) == SIGINT)
					write(STDOUT_FILENO, "\n", 1);
				else if (WTERMSIG(status) == SIGQUIT)
					write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
			}
		}
		pid = waitpid(-1, &status, 0);
	}
	return (last_status);
}

int	add_pipe(int fd[2], t_pipe **pipes)
{
	t_pipe	*new_pipe;

	if (pipe(fd) == -1)
		return (-1);
	new_pipe = malloc(sizeof(t_pipe));
	if (!new_pipe)
		return (-1);
	if (pipes && *pipes)
		new_pipe->next = *pipes;
	else
		new_pipe->next = NULL;
	new_pipe->fd[0] = fd[0];
	new_pipe->fd[1] = fd[1];
	*pipes = new_pipe;
	return (0);
}

int	free_pipes(t_pipe **pipes)
{
	t_pipe	*tmp;

	if (pipes)
		tmp = *pipes;
	else
		return (1);
	while (*pipes && (*pipes)->next)
	{
		tmp = *pipes;
		*pipes = (*pipes)->next;
		free(tmp);
	}
	free(*pipes);
	*pipes = NULL;
	return (0);
}

int	close_origin_fds(int origin_fds[2])
{
	if (origin_fds[0] > 0)
	{
		if (close(origin_fds[0]) == -1)
		{
			close(origin_fds[1]);
			return (-1);
		}
		origin_fds[0] = -1;
	}
	if (origin_fds[1] > 0)
	{
		if (close(origin_fds[1]) == -1)
			return (-1);
		origin_fds[1] = -1;
	}
	return (0);
}
