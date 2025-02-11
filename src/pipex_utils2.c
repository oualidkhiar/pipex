/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhiar <oukhiar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 10:55:42 by oukhiar           #+#    #+#             */
/*   Updated: 2025/02/10 10:56:41 by oukhiar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_open_file(char *file, int in_or_out)
{
	int	ret;

	if (in_or_out == 0)
		ret = open(file, O_RDONLY);
	if (in_or_out == 1)
		ret = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0744);
	if (ret == -1)
	{
		perror("zsh");
		exit(1);
	}
	return (ret);
}

void	ft_handle_failed(void)
{
	perror("Error failed");
	exit(1);
}

void	ft_free(char **adress)
{
	size_t	i;

	i = 0;
	while (adress[i])
	{
		free(adress[i]);
		i++;
	}
	free(adress);
}
