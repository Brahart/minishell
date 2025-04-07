
#include "libft.h"
#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <limits.h>


//recupere une valeur dans l'environnement par sa cle (export, env ET local)
char *get_value(t_env **env, char *key)
{
	char *value;
	t_env *tmp;

	tmp = *env;
	value = NULL;
	while (tmp)
	{
		if (!ft_strncmp(key, tmp->key, ft_strlen(key)))
		{
			value = tmp->value;
			break;
		}
		tmp = tmp->next;
	}
	return (value);
}

/* char *get_home_path(t_env **env) */
/* { */
/* 	t_env *tmp; */
/* 	char *path; */
/**/
/* 	tmp = *env; */
/* 	path = NULL; */
/* 	while (tmp) */
/* 	{ */
/* 		if (!ft_strncmp("HOME", tmp->key, ft_strlen(tmp->key))) */
/* 		{ */
/* 			path = tmp->value; */
/* 			break ; */
/* 		} */
/* 		tmp = tmp->next; */
/* 	} */
/* 	return (path); */
/* } */
/**/
/* char *get_pwd_from_env(t_env **env) */
/* { */
/* 	t_env *tmp; */
/**/
/* 	while (tmp) */
/* 	{ */
/* 		if (!ft_strncmp("PWD", tmp->line, ft_strlen(tmp->line))) */
/* 			break; */
/* 		tmp = tmp->next; */
/* 	} */
/* 	//si on a trouve PWD dans l'env */
/* 	if (tmp) */
/* 		return (tmp->line); */
/* 	else //pas sur du tout de ce qui suit  */
/* 		return (NULL); //Si null c'est qu'on n'a pas trouve */
/* } */

/* int update_old_pwd(char *s) */
/* { */
/* 	//Si PWD n'existe pas  */
/* 	if (!updated_var) */
/* 	{ */
/**/
/* 	} */
/* } */

//env -i bash
//
//env 
//cd ..
//env
//==> OLDPWD existe et est a jour
//env
//unset PWD
//env
//==>Ne doit afficher ni PWD ni OLD_PWD
//env
//unset PWD
//export PWD=lol
//pwd
//env
//==>ne change PAS la variable PWD 
//cd ..
//env 
//==>PWD est a jour et OLD_PWD = lo,
//
//
//Quand on fait cd :
//Si la variable n'existe pas : on annule la mise a jour
//si elle existe, on la met a jour, et on update / cree OLD_PWD
//Si PWD est declaree en locale mais pas exportee : on cree OLDPWD a partir de la varialbe localem mais on ne l'exporte pas PWD
//Dans tous les cas, un echo $PWD doit afficher le path actuel meme si pas exportee
/* int change_directory_and_update_env(t_env **env, char *path) */
/* { */
/* 	char	buf[PATH_MAX]; */
/* 	char *old_pwd; */
/**/
/* 	old_pwd = get_value(env, "PWD"); */
/* 	if (chdir(s) == 0) */
/* 	{ */
/* 		update_old_pwd(old_pwd); */
/* 		getcwd(buf, sizeof(buf)); */
/* 		//securiser !! */
/* 		update_env_var("PWD=", buf); */
/* 	} */
/* 	else */
/* 	{ */
/* 		//dossier introuvable / pas de permissions */
/* 	} */
/* } */
//ajouter l'acces a des dossiers non permis ?
//cd dans un fichier ?
//mkdir -p a/b/c && cd $_
/* int	builtin_cd(char **arg, t_env **env) */
/* { */
/* 	char	*s; */
/**/
	/* char *new_path; */
	/* char	buf[PATH_MAX]; */
	/* new_path = NULL; */
/* 	if (!arg[1]) */
/* 	{ */
/* 		s = get_value(env, "HOME"); // revoir ca */
/* 		if (!s) */
/* 		{ */
/* 			ft_putstr_fd("minishell: cd: HOME not set\n", 1); */
/* 			return (1); */
/* 		} */
/* 		else */
/* 			chdir(s); */
/* 		return (0); */
/* 	} */
/* 	s = ft_strdup(""); */
/* 	if (arg[1][0] && arg[1][0] == '/') // Si on chere cd ~ on doit adapter ca */
/* 	{ */
/* 		if (access(arg[1], F_OK) == 0) */
/* 			chdir(arg[1]); // a proteger ! */
/* 		else */
/* 		{ */
/* 			s = ft_strjoin(s, "minishell: cd: ", s); */
/* 			s = ft_strjoin(s, arg[1], s); */
/* 			s = ft_strjoin(s, ": No such file or directory\n", s); */
/* 			ft_putstr_fd(s, 2); */
/* 			free(s); */
/* 			return (1); */
/* 		} */
/* 	} */
/* 	else if (arg[1][0]) // on est sur un chemin relatif  */
/* 	{ */
/* 		if (access(arg[1], F_OK) == 0) */
/* 			chdir(arg[1]); // a proteger ! */
/* 	} */
	/* free(new_path); */
/* 	free(s); */
/* 	return (0); */
/* } */

t_env **get_key_node(t_env **env, char *key)
{
	t_env **tmp;

	tmp = env;
	if (!key)
		return (NULL);
	while (tmp && *tmp)
	{
		if (!ft_strncmp((*tmp)->key, key, (ft_strlen(key) + 1))) //securiser en comparant la lnonguer dees strs ?
			break;
		*tmp = (*tmp)->next;
	}
	/* #include <stdio.h> */
	/* printf("seek key : %s\nreturned node key : %s\n", key, (*tmp)->key); */
	return (tmp);
}

//Problemes ici !
int swap_and_update_pwd_values(t_env **env)
{
  char    buf[PATH_MAX];
	t_env **pwd_node;
	t_env **oldpwd_node;
	
	pwd_node = get_key_node(env, "PWD");
	oldpwd_node = get_key_node(env, "OLDPWD");
	if (!(*oldpwd_node)->value)
		(*oldpwd_node)->value = ft_strdup((*pwd_node)->value);
	else
  	(*oldpwd_node)->value = (*pwd_node)->value;
  if (getcwd(buf, sizeof(buf)) != NULL)
  {
      free((*pwd_node)->value);
      (*pwd_node)->value = ft_strdup(buf);
  }
  else
  {
      /* perror("getcwd"); */
      return (1);
  }
  return (0);
}

/* If the directory change is successful, cd sets the value of the PWD environment */
/* variable to the new directory name, and sets the OLDPWD environment variable */
/* to the value of the current working directory before the change. */
/* The return status is zero if the directory is successfully changed, non-zero oth- */
/* erwise */

			#include <stdio.h>
int change_directory_and_update_env(t_env **env, char *path)
{

	if (!path)
	{
	#include <stdio.h>
		(void)env;
		printf("path NULL ??\n");
		return (1);
	}
	if (chdir(path) == 0)
	{
		/* #include <stdio.h> */
		/* printf("ici\n"); */
		swap_and_update_pwd_values(env);
		t_env *tmp;

		tmp = *env;
		int i = 1;
		while (tmp)
		{
			printf("ENV : \n");
			printf("#%d\n", i);
			printf("key = %s\n", tmp->key);
			printf("value = %s\n", tmp->key);
			tmp = tmp->next;
			i++;
		}
		return(0);
	}
	else 
		return (1);
}

int is_directory(const char *path)
{
    struct stat statbuf;
    if (stat(path, &statbuf) == 0)
        return S_ISDIR(statbuf.st_mode); // Retourne 1 si c'est un répertoire, 0 sinon
    return 0; // Si stat échoue, ce n'est pas un répertoire
}

int count_args(char** args)
{
	int i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

		 //gerer CDPATH ?
 						 ///* If a non-empty directory name from CDPATH is used, or if ‘-’ is the first argu- */
/* ment, and the directory change is successful, the absolute pathname of the new */
/* working directory is written to the standard output. */
int	builtin_cd(char **arg, t_env **env)
{
	char *s;

	if (count_args(arg) > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (!arg[1])
	{
		s = get_value(env, "HOME"); //a revoir ?
		if (!s)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 1);
			return (1);
		}
		else
			return(change_directory_and_update_env(env, s));
	}
	else
	{
		s = ft_strdup("");
		//si arg[1] == -
			//on cd dans OLDPWD
			//on imprime PWD dans STDOUT
		if (!ft_strncmp(arg[1], "-", ft_strlen(arg[1])))
		{
			if (change_directory_and_update_env(env, get_value(env, "OLDPWD")))
			{
				ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
				return (1);
			}
			else
			{
				s = ft_strjoin(s, get_value(env, "PWD"), s);
				s = ft_strjoin(s, "\n", s);
				ft_putstr_fd(s, 1);
				free(s);
				return (0);
			}
		}
		//Si on decide de gerer CDPATH :
				//d'abord on cherche CDPATH dans l'env
        //si y'en a pas, on continue normalement
 				//si y'en a un : on cherche dans tous ces path si ya un dossier qui correspond
        //si on trouve : on cd dedans et on imprime son pwd
    //si on trouve pas : comme d'hab
		if (is_directory(arg[1])) 
      change_directory_and_update_env(env, arg[1]);
    else
    {
    	if (access(arg[1], F_OK) != 0)
    	{
				s = ft_strjoin("minishell: cd: ", arg[1], s);
    		s = ft_strjoin(s, ": No such file or directory\n", s);
      	ft_putstr_fd(s, 2);
      	free(s);
      	return (1);
    	}
    	else
    	{
				s = ft_strjoin("minishell: cd: Not a directory: ", arg[1], s);
    		s = ft_strjoin(s, "\n", s);
      	ft_putstr_fd(s, 2);
      	free(s);
      	return (1);
      }
    }
		free(s);
  }
	return (0);
}
/* Change the current working directory to directory.
 * If directory is not supplied, the value of the HOME shell variable is used.
 * If the shell variable CDPATH exists, it is used as a search path: each directory name in CDPATH is searched for */
/* directory, with alternative directory names in CDPATH separated by a colon */
/* (‘:’). 
 * If directory begins with a slash, CDPATH is not used. */
/* By default, or when the -L option is supplied, symbolic links in directory are */
/* resolved after cd processes an instance of ‘..’ in directory. */
/* If ‘..’ appears in directory, it is processed by removing the immediately pre- */
/* ceding pathname component, back to a slash or the beginning of directory. */
/* If directory is ‘-’, it is converted to $OLDPWD before the directory change is */
/* attempted. */
/* If a non-empty directory name from CDPATH is used, or if ‘-’ is the first argu- */
/* ment, and the directory change is successful, the absolute pathname of the new */
/* working directory is written to the standard output. */

