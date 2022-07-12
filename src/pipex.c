/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 11:48:21 by anarodri          #+#    #+#             */
/*   Updated: 2022/07/12 12:58:36 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	init_pipex(t_info *data, char **argv, char **envp)
{
	printf("[status:%d]\n", data->status);
	if (pipe(data->end) < 0)
		err_msg(ERR_PIPE, 1);
	if (data->valid_file)
	{
		data->child1 = fork();
		if (data->child1 == 0)
			first_child(*data, argv, envp);
	}
	data->child2 = fork();
	if (data->child2 == 0)
		second_child(*data, argv, envp);
	close(data->end[0]);
	close(data->end[1]);
	if (data->valid_file)
		waitpid(data->child1, &data->status, 0);
	waitpid(data->child2, &data->status, 0);
	printf("[status:%d]\n", data->status);
	free_parent(data);
	if (data->status >> 8 > 0)
		exit(data->status >> 8);
	return (0);
}

void	open_filefd(t_info *data, char **argv)
{
	data->fd_src = open (argv[1], O_RDONLY);
	if (data->fd_src < 0)
	{
		perror(argv[1]);
		data->valid_file = 0;
	}
	else
		data->valid_file = 1;
	data->fd_dst = open (argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (data->fd_dst < 0)
		err_msg(argv[4], 1);
}

int	main(int argc, char **argv, char **envp)
{
	t_info	data;

	if (argc != 5)
		err_msg(ERR_ARGC, 1);
	else
	{
		open_filefd(&data, argv);
		init_struct(&data);
		parse_envp(envp, &data);
		init_pipex(&data, argv, envp);
		exit (EXIT_SUCCESS);
	}
}
