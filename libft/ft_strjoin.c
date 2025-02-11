/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhiar <oukhiar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 21:27:15 by oukhiar           #+#    #+#             */
/*   Updated: 2024/11/12 14:03:31 by oukhiar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_string;
	char	*base_new;
	size_t	len_total;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len_total = ft_strlen(s1) + ft_strlen(s2);
	new_string = (char *)malloc(sizeof(char) * len_total + 1);
	if (new_string == NULL)
		return (NULL);
	base_new = new_string;
	while (*s1)
		*new_string++ = *s1++;
	while (*s2)
		*new_string++ = *s2++;
	*new_string = '\0';
	return (base_new);
}
