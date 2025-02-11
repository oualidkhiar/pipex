/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhiar <oukhiar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:25:29 by oukhiar           #+#    #+#             */
/*   Updated: 2024/11/12 13:29:22 by oukhiar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;
	char	*base_sub;

	if (!s)
		return (0);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	if (start > (unsigned int)ft_strlen(s))
		return (ft_strdup(""));
	sub_str = (char *)malloc(sizeof(char) * len + 1);
	if (sub_str == NULL)
		return (NULL);
	base_sub = sub_str;
	s += start;
	while (len > 0)
	{
		*sub_str++ = *s++;
		len--;
	}
	*sub_str = '\0';
	return (base_sub);
}
