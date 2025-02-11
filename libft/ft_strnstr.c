/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhiar <oukhiar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 21:14:11 by oukhiar           #+#    #+#             */
/*   Updated: 2024/11/15 13:57:27 by oukhiar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;
	size_t	haystack_len;

	if (!len && !haystack && needle)
		return (NULL);
	haystack_len = ft_strlen(haystack);
	needle_len = ft_strlen(needle);
	if (*needle == '\0')
		return ((char *)haystack);
	if (haystack_len < needle_len)
		return (0);
	while (*haystack && len > 0)
	{
		if (len < needle_len)
			return (0);
		if (ft_strncmp(haystack, needle, needle_len) == 0)
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (0);
}
