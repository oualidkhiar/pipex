/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhiar <oukhiar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:52:41 by oukhiar           #+#    #+#             */
/*   Updated: 2024/11/15 09:49:59 by oukhiar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	wie_viel_worter(const char *s, char c)
{
	size_t	flag;
	size_t	i;

	i = 0;
	flag = 1;
	while (*s)
	{
		if (*s == c)
			flag = 1;
		else if (flag)
		{
			i++;
			flag = 0;
		}
		s++;
	}
	return (i);
}

static size_t	ft_len_word(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

static void	*free_split(char **ptr, size_t count)
{
	size_t	i;

	i = 0;
	while (count > i)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (NULL);
}

static char	**ft_alocate_words(const char *s, char c, char **ptr, size_t i)
{
	while (*s)
	{
		if (*s == c)
		{
			s++;
			continue ;
		}
		ptr[i] = ft_substr(s, 0, ft_len_word(s, c));
		if (!ptr[i])
			return (free_split(ptr, i));
		i++;
		s += ft_len_word(s, c);
	}
	ptr[i] = NULL;
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	size_t	count;
	size_t	i;
	char	**ptr;

	i = 0;
	if (s == NULL)
		return (NULL);
	count = wie_viel_worter(s, c);
	ptr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!ptr)
		return (NULL);
	return (ft_alocate_words(s, c, ptr, i));
}
