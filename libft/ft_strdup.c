/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhiar <oukhiar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:37:53 by oukhiar           #+#    #+#             */
/*   Updated: 2024/11/09 17:30:41 by oukhiar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*base_s2;
	size_t	s_len;
	char	*s2;

	s_len = ft_strlen(s1);
	s2 = (char *)malloc(s_len * sizeof(char) + 1);
	if (!s2)
		return (NULL);
	base_s2 = s2;
	while (*s1)
		*s2++ = *s1++;
	*s2 = '\0';
	return (base_s2);
}
