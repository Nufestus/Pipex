/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:58:09 by aammisse          #+#    #+#             */
/*   Updated: 2025/01/27 01:30:49 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/wait.h>
# include <sys/types.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>

typedef struct s_cmd
{
	int		fd[2];
	int		infile;
	int		outfile;
	char	*cmd;
	char	**path;
}				t_cmd;

char	**ft_split(char *s, char c);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, char *src, size_t dstsize);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(char *s);
void	freestr(char **str);
char	*ft_strdup(const char *s1);
char	*getpath(char **av, int arg, t_cmd *process);

#endif