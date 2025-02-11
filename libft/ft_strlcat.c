/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhiar <oukhiar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:46:23 by oukhiar           #+#    #+#             */
/*   Updated: 2024/11/15 14:04:03 by oukhiar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
{
	size_t	src_len;
	size_t	dest_len;
	size_t	counter;

	counter = 0;
	if (!dest && !destsize)
		return (ft_strlen(src));
	src_len = ft_strlen(src);
	dest_len = ft_strlen(dest);
	if (destsize == 0 || destsize <= dest_len)
		return (src_len + destsize);
	dest += dest_len;
	while (*src && counter < destsize - dest_len - 1)
	{
		*dest++ = *src++;
		counter++;
	}
	*dest = '\0';
	return (dest_len + src_len);
}
