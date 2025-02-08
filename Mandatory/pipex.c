/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:52:36 by aammisse          #+#    #+#             */
/*   Updated: 2025/02/07 16:52:59 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	setupchild2(char **av, char **env, t_cmd *process)
{
	dup2(process->fd[0], STDIN_FILENO);
	dup2(process->outfile, STDOUT_FILENO);
	close(process->fd[0]);
	close(process->fd[1]);
	close(process->infile);
	close(process->outfile);
	process->cmd = checkfile(process, av, 3, env);
	execve(process->cmd, process->path, env);
	perror("Path");
	exit(EXIT_FAILURE);
}

void	setupchild1(char **av, char **env, t_cmd *process)
{
	dup2(process->infile, STDIN_FILENO);
	dup2(process->fd[1], STDOUT_FILENO);
	close(process->fd[0]);
	close(process->fd[1]);
	close(process->infile);
	close(process->outfile);
	process->cmd = checkfile(process, av, 2, env);
	execve(process->cmd, process->path, env);
	perror("Path");
	exit(EXIT_FAILURE);
}

int	checkargs(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (av[i][0] == '\0')
			return (0);
		i++;
	}
	return (1);
}

void	exec(char **av, char **env, t_cmd *process)
{
	pid_t	pid1;
	pid_t	pid2;

	pid1 = fork();
	if (pid1 == 0)
		setupchild1(av, env, process);
	pid2 = fork();
	if (pid2 == 0)
		setupchild2(av, env, process);
	close(process->fd[0]);
	close(process->fd[1]);
	waitpid(-1, 0, 0);
}

int	main(int ac, char **av, char **env)
{
	t_cmd	process;

	if (ac != 5 || !checkargs(av))
	{
		write(2, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 40);
		return (EXIT_FAILURE);
	}
	process.infile = open(av[1], O_RDONLY, 0777);
	if (access(av[1], F_OK | R_OK) == -1)
	{
		perror("Error");
		exit(0);
	}
	process.outfile = open(av[4], O_RDWR | O_TRUNC | O_CREAT, 0766);
	if (pipe(process.fd) == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	exec(av, env, &process);
	return (0);
}
