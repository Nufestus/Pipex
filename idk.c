/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   idk.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:55:52 by aammisse          #+#    #+#             */
/*   Updated: 2025/01/25 16:01:35 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd1(int file, int pipe_fd[2], char *cmd1_path, char **cmd1_args, char **envp)
{
	dup2(file, STDIN_FILENO); // Redirect stdout to pipe
	dup2(pipe_fd[1], STDOUT_FILENO);
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    close(file);
	execve(cmd1_path, cmd1_args, envp);
	perror("execve failed");
	exit(EXIT_FAILURE);
}

void	exec_cmd2(int file, int pipe_fd[2], char *cmd2_path, char **cmd2_args, char **envp)
{
	dup2(pipe_fd[0], STDIN_FILENO); // Redirect stdin to pipe
	dup2(file, STDOUT_FILENO);
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    close(file);
	execve(cmd2_path, cmd2_args, envp);
	perror("execve failed");
	exit(EXIT_FAILURE);
}

int main(int ac, char *av[], char *env[])
{
    // int i;
    // int pid;
    // char *buffer;
    // int pipefd[2];
    // char *message = "hello world";

    // buffer = malloc(1000);
    // if (pipe(pipefd) == -1)
    // {
    //     dup2(3, 1);
    //     pprint
    //     perror("pipe");
    //     exit(1);
    // }
    // pid = fork();
    // if (pid == -1)
    // {
    //     perror("fork");
    //     return 0;
    // }
    // if (pid == 0)
    // {
    //     close(pipefd[1]);
    //     read(pipefd[1], buffer, sizeof(buffer));
    //     printf("Child got %s\n", buffer);
    //     close(pipefd[0]);
    // }
    // else
    // {
    //     close(pipefd[0]);
    //     write(pipefd[1], message, strlen(message) + 1);
    //     close(pipefd[1]);
    // }
    // int fd = open("txt", O_RDWR);
    // dup2(fd, 1);
    // printf("HAHA\n");
    // int fd[2];
    // pipe(fd);
    // int x = fork();
    // int status = 134486;
    // if (x == 0)
    // {
    //     close(fd[0]);
    //     dup2(fd[1], 1);
    //     printf("Hello from child\n");
    //     close(fd[1]);
    // }
    // else
    // {
    //     char buf[1024];
    //     close(fd[1]);
    //     dup2(fd[0], 0);
    //     read(0, buf, 1024);
    //     printf("%s\n", buf);


    //     printf("%d\n", status >> 8);
    // }
    
    //  while (i < 5)
    //   pipe(fd)
    //   fork()
    //   if(pid == 0)
    //     child labor
    // i++;
    // }
    // while (i < 5)
    // {
    //     waitpid(pids[i], NULL, 0);
    //     i++;
    // }
    // exit(0);
    // // execve("/bin/ls", "file1", env);
    // errno = ERANGE;
    // exit(errno);
    // char buf[1024];
    // read(0, buf, 1024);
    int i;
    int fd[2];
    t_cmd process;
    t_cmd process2;
    
    i = 0;
    int outfile = open(av[4], O_RDWR | O_TRUNC | O_CREAT, 0777);
    if (access("infile", F_OK | R_OK) == -1)
    {
        perror("Error");
        exit(0);
    }
    int infile = open(av[1], O_RDONLY, 0777);
    process.cmd = ft_split(av[2], ' ');
    process2.cmd = ft_split(av[3], ' ');
    if (ac != 5)
	{
		write(2, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 40);
		return (EXIT_FAILURE);
	}
	if (pipe(fd) == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
    process.pid = fork();
    if (process.pid == 0)
        exec_cmd1(infile, fd, process.cmd[0], process.cmd, env);
    process2.pid = fork();
    if (process2.pid == 0)
        exec_cmd2(outfile, fd, process2.cmd[0], process2.cmd, env);
        
    close(fd[0]);
	close(fd[1]);

	waitpid(process.pid, NULL, 0); // Waits for cmd1
	waitpid(process2.pid, NULL, 0); // Waits for cmd2
    
    close(infile);
    close(outfile);
}
