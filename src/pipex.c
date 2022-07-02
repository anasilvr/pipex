/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 11:48:21 by anarodri          #+#    #+#             */
/*   Updated: 2022/07/02 14:53:10 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	initPipex(t_info *data, char **envp)
{
//	getSrcFD(argv[1], data);
//	getDstFD(argv[argc - 1], data);
	if (pipe(data->end) < 0)
		errMsg(ERR_PIPE, 1);

	data->child1 = fork();
	if (data->child1 == 0)
		firstChild(*data, envp);

	data->child2 = fork();
	if (data->child2 == 0)
		secondChild(*data, envp);

	close(data->end[0]);
	close(data->end[1]);
	waitpid(data->child1, &data->status, 0);
	waitpid(data->child2, &data->status, 0);

	freeParent(data);

	if (data->status >> 8 > 0)
		exit (data->status >> 8);

	return;
}

int	main(int argc, char **argv, char **envp)
{
	t_info data;

	if (argc != 5)
		errMsg(ERR_ARGC, 1);

	data.fd_src = open (argv[1], O_RDONLY);
	data.fd_dst = open (argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (data.fd_src < 0 || data.fd_dst < 0)
		errMsg(ERR_OPEN, -1);

	parseInput(argv, envp, &data);

	initPipex(&data, envp);
	return (0);
//	if (data.valid_file != 0)
//	{
//		data.child1 = fork();
//		if (data.child1 == 0)
//			firstChild(argv, envp, data);
//	}
}