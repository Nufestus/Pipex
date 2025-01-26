/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:52:36 by aammisse          #+#    #+#             */
/*   Updated: 2025/01/26 16:38:30 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void freestr(char **str)
{
    int i;

    i = 0;
    while(str[i])
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

// void checkcmd(char *cmd, char **av, char **env, int file)
// {
//     char **args;
//     args = ft_split(av[av], ' ');
//     if (process->pid == 0 && process->av == 2)
//         exec_cmd1(file, process->fd, process->cmd, process->args, env);
//     else if (process->pid == 0 && process->av == 3)
//         exec_cmd2(file, process->fd, process->cmd, process->args, env);
//     waitpid(-1, NULL, 0);
//     close(process->fd[0]);
//     close(process->fd[1]);
// }

char *checkfile(t_cmd *process, char **av, int arg, char **env)
{
    int i;
    char *str;
    char **path;
    
    i = 0;
    while(strncmp(env[i], "PATH", 4))
        i++;
    path = ft_split(env[i] + 5, ':');
    process->path = ft_split(av[arg], ' ');
    i = 0;
    while(path[i])
    {
        str = ft_strjoin(path[i], "/");
        str = ft_strjoin(str, process->path[0]);
        if (!access(str, F_OK | X_OK))
            return ft_strdup(str);
        i++;
    }
    freestr(path);
    return NULL;
}

void setupchild2(char **av, char **env, t_cmd *process)
{
    dup2(process->fd[0], STDIN_FILENO);
	dup2(process->outfile, STDOUT_FILENO);
    close(process->fd[0]);
    close(process->fd[1]);
    close(process->outfile);
    process->cmd = checkfile(process, av, 3, env);
	execve(process->cmd, process->path, env);
	perror("Error");
	exit(EXIT_FAILURE);
}

void setupchild1(char **av, char **env, t_cmd *process)
{
    dup2(process->infile, STDIN_FILENO);
	dup2(process->fd[1], STDOUT_FILENO);
    close(process->fd[0]);
    close(process->fd[1]);
    close(process->infile);
    process->cmd = checkfile(process, av, 2, env);
	execve(process->cmd, process->path, env);
	perror("Error");
	exit(EXIT_FAILURE);
}

void exec(char **av, char **env, t_cmd *process)
{
    pid_t pid1;
    pid_t pid2;
    
    pid1 = fork();
    if (pid1 == 0)
        setupchild1(av, env, process);
    pid2 = fork();
    if (pid2 == 0)
        setupchild2(av, env, process);
    close(process->fd[0]);
    close(process->fd[1]);
    waitpid(pid1, 0, 0);
    waitpid(pid2, 0, 0);
}


int main(int ac, char **av, char **env)
{
    int i;
    t_cmd process;

    i = 0;
    if (ac != 5 || av[2][0] == '\0' || av[3][0] == '\0')
	{
		write(2, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 40);
		return (EXIT_FAILURE);
	}
    process.infile = open(av[1], O_RDONLY, 0777);
    process.outfile = open(av[4], O_RDWR | O_TRUNC | O_CREAT, 0777);
    if (access(av[1], F_OK | R_OK) == -1)
    {
        perror("Error");
        exit(0);
    }
    if (pipe(process.fd) == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
    exec(av, env, &process);
}