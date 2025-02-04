/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 01:38:18 by aammisse          #+#    #+#             */
/*   Updated: 2025/02/04 16:37:23 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <sys/wait.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include "GNL/get_next_line_bonus.h"

typedef struct s_process
{
	int		index;
	int		infile;
	int		outfile;
	int		originaloutfile;
	int		outcheck;
	int		heredoc;
	int		ac;
	char	**av;
	char	*cmd;
	char	**path;
}				t_process;

char	**ft_split(char *s, char c);
int		execheredoc(t_process *process);
void	here_doc(char *limiter, int fd);
int		ft_strcmp(char *s1, char *s2);
char	*getpath(char **av, int arg, t_process *process);
void	freestr(char **str);
char	*checkfile(t_process *process, int arg, char **env);
int		checkargs(char **av);
void	errorexit(char *error);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	getfds(t_process *process, int fd);

#endif