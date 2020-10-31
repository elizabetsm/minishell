/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 17:40:48 by efleta            #+#    #+#             */
/*   Updated: 2019/09/24 13:23:55 by efleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_count_words(char const *s, char *separators)
{
	size_t words;

	words = 0;
	while (*s)
	{
		while (contains_symbol(separators, *s))
			s++;
		if (*s)
		{
			words++;
			while (*s && !contains_symbol(separators, *s))
				s++;
		}
	}
	return (words);
}

static char		*ft_get_word(char *word, char *separators)
{
	char *start;

	start = word;
	while (*word && !contains_symbol(separators, *word))
		word++;
	*word = '\0';
	return (ft_strdup(start));
}

static void		ft_free_words(char **words, size_t i)
{
	while (i--)
		ft_strdel(&(words[i]));
	free(*words);
}

static char		**ft_get_words(char *s, char *separators, size_t words_count)
{
	char	**words;
	char	*word;
	size_t	i;

	i = 0;
	if ((words = (char **)ft_memalloc(sizeof(char *) * (words_count + 1))))
	{
		while (i < words_count)
		{
			while (contains_symbol(separators, *s))
				s++;
			if (*s)
			{
				if (!(word = ft_get_word(s, separators)))
				{
					ft_free_words(words, i);
					return (NULL);
				}
				words[i++] = word;
				s += (ft_strlen(word) + 1);
			}
		}
		words[i] = NULL;
	}
	return (words);
}

char			**ft_strsplit2(char const *s, char *separators)
{
	char	**words;
	char	*line;
	int		i;

	if (!s || !(line = ft_strdup((char *)s)))
		return (NULL);
	i = ft_count_words(line, separators);
	if (i == 0)
		return (NULL);
	words = ft_get_words(line, separators, i);
	ft_strdel(&line);
	return (words);
}
