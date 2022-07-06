/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 11:48:21 by anarodri          #+#    #+#             */
/*   Updated: 2022/07/06 18:14:51 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	init_pipex(t_info *data, char **argv, char **envp)
{
	if (pipe(data->end) < 0)
		err_msg(ERR_PIPE, 1);
	data->child1 = fork();
	if (data->child1 == 0)
		first_child(*data, argv, envp);
	data->child2 = fork();
	if (data->child2 == 0)
		second_child(*data, argv, envp);
	close(data->end[0]);
	close(data->end[1]);
	waitpid(data->child1, &data->status, 0);
	waitpid(data->child2, &data->status, 0);
	free_parent(data);
	if (data->status >> 8 > 0)
		exit(data->status >> 8);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_info	data;

	if (argc != 5)
		err_msg(ERR_ARGC, 1);
	data.fd_src = open (argv[1], O_RDONLY);
	if (data.fd_src < 0)
		perror(argv[1]);
	data.fd_dst = open (argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (data.fd_dst < 0)
		err_msg(argv[4], 1);
	init_struct(&data);
	parse_envp(envp, &data);
	init_pipex(&data, argv, envp);
	return (0);
}
