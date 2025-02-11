/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhiar <oukhiar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 11:25:41 by oukhiar           #+#    #+#             */
/*   Updated: 2024/11/10 14:12:45 by oukhiar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	result;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		n *= (-1);
		write(fd, "-", 1);
	}
	if (n >= 0 && n <= 9)
	{
		result = n + '0';
		write(fd, &result, 1);
	}
	if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		result = n % 10;
		result = result + '0';
		write(fd, &result, 1);
	}
}
