/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:51:13 by aammisse          #+#    #+#             */
/*   Updated: 2025/02/04 16:09:58 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void here_doc(char *limiter, int fd)
{
	char *line;

	while(1)
	{
		write(0, "heredoc> ", 10);
		line = get_next_line(0);
		if (!line || !ft_strcmp(line, limiter))
		{
			free(line);
			break;
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
	char *limiter;
	int fd[2];
	
	if (pipe(fd) == -1)
		errorexit("Pipe Failed");
	limiter = ft_strjoin(process->av[2], "\n");
	if (!limiter)
		errorexit("Malloc failed");
	here_doc(limiter, fd[1]);
	waitpid(-1, 0, 0);
	return (fd[0]);
}
