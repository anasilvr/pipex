/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 11:48:25 by anarodri          #+#    #+#             */
/*   Updated: 2022/07/03 21:21:12 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	firstChild(t_info data, char **argv, char **envp)
{
	int	errnum;

	errnum = 0;
	dup2(data.end[1], STDOUT_FILENO);
	close(data.end[0]);
	dup2(data.fd_src, STDIN_FILENO);

	data.cmd_args = ft_split(argv[2], ' ');
	data.cmd = getCmdPath(data.cmd_path, data.cmd_args[0]);

	if (!data.cmd)
	{
		errChild(ERR_CMD, data.cmd_args[0]);
		errnum = 127;
	}
	else if (execve(data.cmd, data.cmd_args, envp) == -1)
	{
		errChild(ERR_CMD, data.cmd);
		errnum = 127;
	}

	freeChild(&data);

	if (errnum != 0)
		exit(errnum);
}

void	secondChild(t_info data, char **argv, char **envp)
{
	int	errnum;

	errnum = 0;
	dup2(data.end[0], STDIN_FILENO);
	close(data.end[1]);
	dup2(data.fd_dst, STDOUT_FILENO);

	data.cmd_args = ft_split(argv[3], ' ');

	data.cmd = getCmdPath(data.cmd_path, data.cmd_args[0]);
	if(!data.cmd)
	{
		errChild(ERR_CMD, data.cmd_args[0]);
		errnum = 127;
	}
	else if (execve(data.cmd, data.cmd_args, envp) == -1)
	{
		errChild(ERR_CMD, data.cmd);
		errnum = 127;
	}

	freeChild(&data);
	if (errnum != 0)
		exit(errnum);
}

void	freeChild(t_info *data)
{
	int	i;

	i = 0;
	if (data->cmd_args)
	{
		while (data->cmd_args[i++])
			free(data->cmd_args[i]);
		free(data->cmd_args);
	}
	// i = 0;
	// if (data->cmd2_args)
	// {
	// 	while (data->cmd2_args[i++])
	// 		free(data->cmd2_args[i]);
	// 	free(data->cmd2_args);
	// }
	//if(data->cmd)
		free(data->cmd);
}

void	freeParent(t_info *data)
{
	int	i;

	i = 0;
	while(data->cmd_path[i])
	{
		free(data->cmd_path[i]);
		i++;
	}
	free(data->cmd_path);
	close(data->fd_src);
	close(data->fd_dst);
}