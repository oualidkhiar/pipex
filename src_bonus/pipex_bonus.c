/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukhiar <oukhiar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:06:59 by oukhiar           #+#    #+#             */
/*   Updated: 2025/02/11 12:58:27 by oukhiar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_get_index(int count, char *str)
{
	int	ret;

	if (check_here_doc(str))
		ret = count + 3;
	else
		ret = count + 2;
	return (ret);
}

void	ft_handle_cases(t_usage variabls, char **av, char **env, int ac)
{
	int	index_cmd;

	index_cmd = ft_get_index(variabls.i, av[1]);
	if (variabls.i == 0)
	{
		if (!first_child(variabls.p_fd[variabls.i], \
		variabls.fd_in, env, av[index_cmd]))
			ft_free_pipes(variabls.p_fd);
		exit(1);
	}
	else if (variabls.i == variabls.count - 1)
	{
		if (!last_child_procces(variabls.p_fd[variabls.i - 1], \
		variabls.fd_out, env, av[ac - 2]))
			ft_free_pipes(variabls.p_fd);
		exit(1);
	}
	else
	{
		if (!two_child(variabls.p_fd[variabls.i - 1], \
		variabls.p_fd[variabls.i], env, av[index_cmd]))
			ft_free_pipes(variabls.p_fd);
		exit(1);
	}
}

t_usage	ft_initialize(t_usage values, char **av, int ac, int count)
{
	values.count = count;
	values.i = 0;
	if (check_here_doc(av[1]))
		values.fd_in = get_in_file_from_here_doc(av[2]);
	else
		values.fd_in = get_in_file_from_file(av[1]);
	values.fd_out = get_out_file_fd(av[ac - 1], av[1]);
	if (values.fd_in == -1 || values.fd_out == -1)
		exit(1);
	values.p_fd = ft_alocate_pipes(count);
	return (values);
}

void	ft_reduce(char **av, char **env, int count, int ac)
{
	t_usage	values;

	values = ft_initialize(values, av, ac, count);
	while (values.i < count)
	{
		if (values.i != count - 1)
		{
			if (pipe(values.p_fd[values.i]) == -1)
			{
				ft_putstr_fd("pipe failed !!\n", 2);
				exit(1);
			}
		}
		values.child_pid = fork();
		if (values.child_pid == 0)
			ft_handle_cases(values, av, env, ac);
		else
			ft_close_pipes(values);
		values.i++;
	}
	close(values.fd_in);
	close(values.fd_out);
	ft_free_pipes(values.p_fd);
}

int	main(int ac, char **av, char **env)
{
	int	count;
	int	i;

	i = 0;
	count = ac - 3;
	if (ac < 5)
	{
		ft_putstr_fd("Argument not valid EX: <infile CMD1\
		CMD2 CMD3 >outfile\n", 2);
		exit (1);
	}
	if (check_here_doc(av[1]))
	{
		if (ac < 6)
		{
			ft_putstr_fd("Argument not valid EX: <here_doc DILIMETE\
			CMD1 CMD2 >outfile\n", 2);
			exit (1);
		}
		else
			count = ac - 4;
	}
	ft_reduce(av, env, count, ac);
	while (i++ < count)
		waitpid(0, NULL, 0);
}
