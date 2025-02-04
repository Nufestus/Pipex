/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 20:09:10 by aammisse          #+#    #+#             */
/*   Updated: 2025/02/04 16:34:11 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*copy;
	char	*str;

	i = 0;
	str = (char *)s1;
	copy = (char *) malloc(ft_strlen(str) + 1);
	if (copy == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*getpath(char **av, int arg, t_cmd *process)
{
	process->path = ft_split(av[arg], ' ');
	if (access(process->path[0], F_OK | X_OK) == -1)
	{
		perror("Error");
		exit(errno);
	}
	return (process->path[0]);
}

char	*checkfile(t_cmd *process, char **av, int arg, char **env)
{
	int		i;
	char	*str;
	char	**path;

	i = 0;
	while (strncmp(env[i], "PATH", 4))
		i++;
	if (av[arg][0] == '.' && av[arg][1] == '/')
		return (getpath(av, arg, process));
	path = ft_split(env[i] + 5, ':');
	process->path = ft_split(av[arg], ' ');
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
