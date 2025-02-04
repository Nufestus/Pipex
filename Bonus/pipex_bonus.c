/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:23:01 by aammisse          #+#    #+#             */
/*   Updated: 2025/02/04 16:37:03 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	makechildren(t_process *process, char **env, int index)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		errorexit("pipe failed");
	getfds(process, fd[1]);
	pid = fork();
	if (!pid)
	{
		close(fd[0]);
		if (dup2(process->infile, 0) == -1)
			errorexit("dup2 infile failed");
		close(process->infile);
		if (dup2(process->outfile, 1) == -1)
			errorexit("dup2 outfile failed");
		close(process->outfile);
		process->cmd = checkfile(process, index, env);
		if (!process->cmd)
			errorexit("Not A Valid Command");
		execve(process->cmd, process->path, env);
	}
	close(fd[1]);
	close(process->infile);
	process->infile = fd[0];
}

void	startpipex(t_process *process, char **env)
{
	while (process->index < process->ac - 1)
	{
		if (process->index == process->ac - 2)
			process->outcheck = 1;
		makechildren(process, env, process->index);
		process->index++;
	}
	close(process->infile);
	close(process->originaloutfile);
	waitpid(-1, 0, 0);
}

void	initdata(t_process *process, char **av, int ac)
{
	process->heredoc = 0;
	process->outfile = open(av[ac - 1], O_RDWR | O_TRUNC | O_CREAT);
	if (process->outfile == -1)
	{
		perror("open");
		exit(0);
	}
	process->originaloutfile = process->outfile;
	process->outcheck = 0;
	process->index = 2;
	process->av = av;
	process->ac = ac;
}

void	errorexit(char *error)
{
	if (error)
	{
		write(1, error, ft_getstrlen(error) + 1);
		exit(1);
	}
	return ;
}

int	main(int ac, char **av, char **env)
{
	t_process	process;

	if (ac < 5)
		errorexit("Not Enough Arguments!");
	initdata(&process, av, ac);
	if (!ft_strcmp(av[1], "here_doc"))
	{
		if (ac < 6)
			errorexit("Not Enough Arguments!");
		process.index = 3;
		process.heredoc = 1;
		process.infile = execheredoc(&process);
	}
	else
	{
		process.infile = open(av[1], O_RDONLY);
		if (process.infile == -1)
		{
			perror("open");
			exit(0);
		}
	}
	startpipex(&process, env);
	exit(0);
}
