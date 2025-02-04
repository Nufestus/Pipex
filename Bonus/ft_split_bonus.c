/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aammisse <aammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 21:41:51 by aammisse          #+#    #+#             */
/*   Updated: 2025/02/03 14:59:20 by aammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// char	*ft_strdup(char *s)
// {
//     char *dup = malloc(strlen(s) + 1);
//     if (!dup)
//         return (NULL);
//     strcpy(dup, s);
//     return (dup);
// }

// char	*ft_strjoin(char *s1, char *s2)
// {
//     char *joined;
//     size_t len = strlen(s1) + strlen(s2) + 1;
//     joined = malloc(len);
//     if (!joined)
//         return (NULL);
//     strcpy(joined, s1);
//     strcat(joined, s2);
//     return (joined);
// }

void free_str_array(char **arr)
{
    int i = 0;
    while (arr[i])
        free(arr[i++]);
    free(arr);
}

// Basic ft_split (simplified version)
char	**ft_split(char *s, char c)
{
    int i = 0, j = 0, start, word_count = 1;
    while (s[i]) // Count words
        if (s[i++] == c)
            word_count++;
    char **result = malloc(sizeof(char *) * (word_count + 1));
    if (!result)
        return (NULL);
    i = 0;
    while (s[i]) // Split words
    {
        while (s[i] == c)
            i++;
        start = i;
        while (s[i] && s[i] != c)
            i++;
        if (i > start)
        {
            result[j] = strndup(s + start, i - start);
            j++;
        }
    }
    result[j] = NULL;
    return (result);
}
