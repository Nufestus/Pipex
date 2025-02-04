/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:35:20 by aammisse          #+#    #+#             */
/*   Updated: 2025/02/04 16:37:18 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

char	*getpath(char **av, int arg, t_process *process)
{
	process->path = ft_split(av[arg], ' ');
	if (access(process->path[0], F_OK | X_OK) == -1)
	{
		perror("Error");
		exit(errno);
	}
	return (process->path[0]);
}

void	freestr(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	*checkfile(t_process *process, int arg, char **env)
{
	int		i;
	char	*str;
	char	**path;

	i = 0;
	while (ft_strncmp(env[i], "PATH", 4))
		i++;
	if (!env[i])
		return (NULL);
	if (process->av[arg][0] == '.' && process->av[arg][1] == '/')
		return (getpath(process->av, arg, process));
	path = ft_split(env[i] + 5, ':');
	process->path = ft_split(process->av[arg], ' ');
	i = 0;
	while (path[i])
	{
		str = ft_strjoin(path[i], "/");
		str = ft_strjoin(str, process->path[0]);
		if (!access(str, F_OK | X_OK))
			return (ft_strdup(str));
		i++;
	}
	freestr(path);
	return (NULL);
}

void	getfds(t_process *process, int fd)
{
	if (process->outcheck)
	{
		close(fd);
		process->outfile = process->originaloutfile;
	}
	else
		process->outfile = fd;
}
