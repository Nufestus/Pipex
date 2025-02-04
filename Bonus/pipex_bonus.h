/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 01:38:18 by aammisse          #+#    #+#             */
/*   Updated: 2025/02/04 12:51:06 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

#include <sys/wait.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include "GNL/get_next_line_bonus.h"

typedef struct s_process
{
	int		index;
	int		prevpipe;
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
void	free_str_array(char **arr);
int	execheredoc(t_process *process);
void	here_doc(char *limiter, int fd);
int		ft_strcmp(char *s1, char *s2);
char	*getpath(char **av, int arg, t_process *process);
void	freestr(char **str);
char	*checkfile(t_process *process, int arg, char **env);
int		checkargs(char **av);
void	errorexit(char *error);

#endif