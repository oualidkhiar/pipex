/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_managment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhiar <oukhiar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 21:16:30 by oukhiar           #+#    #+#             */
/*   Updated: 2025/02/10 11:04:00 by oukhiar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	*ft_malloc(size_t size)
{
	void	*p;

	p = malloc(size);
	if (p == NULL)
	{
		ft_putstr_fd("Memory allocation failed !!\n", 2);
		exit(1);
	}
	return (p);
}

int	**ft_alocate_pipes(int count)
{
	int	**pipes;
	int	i;	

	i = 0;
	pipes = ft_malloc(sizeof(int *) * count);
	while (i < count - 1)
	{
		pipes[i] = ft_malloc(sizeof(int) * 2);
		i++;
	}
	pipes[i] = NULL;
	return (pipes);
}

void	ft_free_pipes(int **address_pipes)
{
	int	i;

	i = 0;
	while (address_pipes[i] != NULL)
	{
		free(address_pipes[i]);
		i++;
	}
	free(address_pipes);
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

void	ft_close_pipes(t_usage values)
{
	if (values.i > 0)
		close(values.p_fd[values.i - 1][0]);
	if (values.i != values.count - 1)
		close(values.p_fd[values.i][1]);
}
