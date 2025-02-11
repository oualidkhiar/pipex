/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhiar <oukhiar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:08:06 by oukhiar           #+#    #+#             */
/*   Updated: 2024/11/12 13:35:19 by oukhiar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	countlen(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (set[j] && s1[i])
	{
		if (set[j] == s1[i])
		{
			i++;
			j = 0;
		}
		else
			j++;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	last_s1;

	if (!s1 || !set)
		return (0);
	j = 0;
	i = countlen(s1, set);
	last_s1 = ft_strlen(s1) - 1;
	if (i > last_s1)
		return (ft_substr(s1, 0, 0));
	while (set[j] && s1[last_s1])
	{
		if (set[j] == s1[last_s1])
		{
			last_s1--;
			j = 0;
		}
		else
			j++;
	}
	return (ft_substr(s1, i, last_s1 - i + 1));
}
