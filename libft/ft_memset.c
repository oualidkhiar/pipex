/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhiar <oukhiar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:46:35 by oukhiar           #+#    #+#             */
/*   Updated: 2024/11/17 09:42:30 by oukhiar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*po;
	size_t			i;

	i = 0;
	po = (unsigned char *)b;
	while (i < len)
	{
		po[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
