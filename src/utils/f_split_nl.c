/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_split_nl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:28:35 by bbierman          #+#    #+#             */
/*   Updated: 2025/03/11 12:09:08 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static char	**free_array(char **arr, int i);
static unsigned int	word_count(char const *s, char c);
static char	*fill_word(char const *s, int start, int end);
static char	**fill_array(char **split, char const *s, char c);

char	**f_split_nl(char const *s, char c)
{
	unsigned int	wordcount;
	char			**return_array;
	char			**split;

	wordcount = word_count(s, c);
	split = (char **) malloc((wordcount + 1) * sizeof(char *));
	if (!split)
		return (0);
	return_array = fill_array(split, s, c);
	if (return_array == NULL)
		return (0);
	return (return_array);
}

static char	**free_array(char **arr, int i)
{
	while (i >= 0)
	{
		free(arr[i]);
		i--;
	}
	free(arr);
	return (0);
}

static unsigned int	word_count(char const *s, char c)
{
	int	word_count;

	word_count = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			while (*s && *s != c)
				s++;
			word_count++;
		}
	}
	return (word_count);
}

static char	*fill_word(char const *s, int start, int end)
{
	char	*word;

	word = (char *) malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	ft_memcpy(word, s + start, end - start);
	word[end - start] = '\0';
	return (word);
}

static char	**fill_array(char **split, char const *s, char c)
{
	size_t	i;
	int		j;
	int		index;
	int		wordcount;

	i = 0;
	j = 0;
	index = -1;
	wordcount = word_count(s, c);
	while (j < wordcount)
	{
		if (s[i - 1] == c && s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			split[j] = fill_word(s, index, i);
			if (!split[j])
				return (free_array(split, j));
			index = -1;
			j++;
		}
		i++;
	}
	split[j] = NULL;
	return (split);
}
