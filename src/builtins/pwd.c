

#include "libft.h"
#include "minishell.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// des cas nuls ?
// tester en unsetant PWD ...
// tester un unset avec un env vide
int	builtin_pwd(void)
{
	char	buf[PATH_MAX];
	char	*s;

	s = NULL;
	if (getcwd(buf, sizeof(buf)) != NULL)
	{
		s = ft_strjoin(buf, "\n");
		ft_putstr_fd(s, 1);
		free(s);
		return (0);
	}
	else
	{
		perror("pwd");
		//  1 ou errno ?
		return (1);
	}
	return (0);
}

/* Print the absolute pathname of the current working directory. If the
	-P option */
/* is supplied, the pathname printed will not contain symbolic links. If the
	-L */
/* option is supplied, the pathname printed may contain symbolic links. The */
/* return status is zero unless an error is encountered while determining the name */
/* of the current directory or an invalid option is supplied. */
