/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 21:41:51 by aammisse          #+#    #+#             */
/*   Updated: 2025/02/04 16:19:46 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static size_t	count_words(char *s, char c)
{
	unsigned int	i;
	size_t			word;

	i = 0;
	word = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			word++;
		i++;
	}
	return (word);
}

static size_t	str_length(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	**free_mem(char **s, int i)
{
	int	index;

	index = 0;
	while (index < i)
	{
		free(s[index]);
		index++;
	}
	free(s);
	return (NULL);
}

char	**ft_split(char *s, char c)
{
	size_t	k;
	size_t	index;
	char	**p;

	if (!s)
		return (NULL);
	k = count_words((char *)s, c);
	index = 0;
	p = (char **) malloc((sizeof(char *)) * (k + 1));
	if (!p)
		return (NULL);
	while (index < k)
	{
		while (*s == c)
			s++;
		p[index] = (char *)malloc((sizeof(char) * (str_length(s, c) + 1)));
		if (!p[index])
			return (free_mem(p, index));
		ft_strlcpy(p[index], s, str_length(s, c) + 1);
		s = s + str_length(s, c);
		index++;
	}
	p[index] = NULL;
	return (p);
}
