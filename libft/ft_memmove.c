/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhiar <oukhiar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 22:45:31 by oukhiar           #+#    #+#             */
/*   Updated: 2024/11/12 12:12:02 by oukhiar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char	*dest_ptr;
	char	*src_ptr;

	dest_ptr = (char *)dest;
	src_ptr = (char *)src;
	if (!dest && !src)
		return (0);
	dest_ptr += len;
	src_ptr += len;
	if (dest > src)
	{
		while (len--)
			*(--dest_ptr) = *(--src_ptr);
	}
	else
		ft_memcpy(dest, src, len);
	return (dest);
}
