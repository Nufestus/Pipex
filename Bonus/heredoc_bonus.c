/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:51:13 by aammisse          #+#    #+#             */
/*   Updated: 2025/02/06 17:27:48 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	handle(unsigned char c, unsigned char b)
{
	if (c - b > 0)
		return (1);
	else if (c - b < 0)
		return (-1);
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while ((str1[i] != '\0' || str2[i] != '\0') && i < n)
	{
		if (str1[i] != str2[i])
			return (handle(str1[i], str2[i]));
		i++;
	}
	return (0);
}

void	here_doc(char *limiter, int fd)
{
	char	*line;

	while (1)
	{
		write(0, "heredoc> ", 10);
		line = get_next_line(0);
		if (!line || !ft_strcmp(line, limiter))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_getstrlen(line));
		free(line);
	}
	free(limiter);
	close(fd);
	return ;
}

int	execheredoc(t_process *process)
{
	char	*limiter;
	int		fd[2];

	if (pipe(fd) == -1)
		errorexit("Pipe Failed");
	limiter = ft_strjoin(process->av[2], "\n");
	if (!limiter)
		errorexit("Malloc failed");
	here_doc(limiter, fd[1]);
	return (fd[0]);
}
