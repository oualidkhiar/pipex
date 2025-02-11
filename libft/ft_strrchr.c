/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhiar <oukhiar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:27:31 by oukhiar           #+#    #+#             */
/*   Updated: 2024/11/09 21:42:49 by oukhiar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len_s;

	len_s = ft_strlen(s);
	while (len_s >= 0)
	{
		if (*(s + len_s) == (char)c)
			return ((char *)s + len_s);
		len_s--;
	}
	return (0);
}
