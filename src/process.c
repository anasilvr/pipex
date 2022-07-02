/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 11:48:25 by anarodri          #+#    #+#             */
/*   Updated: 2022/07/02 15:30:42 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	firstChild(t_info data, char **envp)
{
	int	errnum;

	errnum = 0;
	dup2(data.end[1], STDOUT_FILENO);
	close(data.end[0]);
	dup2(data.fd_src, STDIN_FILENO);

	data.cmd = getCmdPath(data.cmd_path, data.cmd1_args[0]);

	if (!data.cmd)
	{
		errChild(ERR_CMD, data.cmd1_args[0]);
		errnum = 127;
	}
	else if (execve(data.cmd, data.cmd1_args, envp) == -1)
	{
		errChild(ERR_CMD, data.cmd);
		errnum = 127;
	}

	freeChild(&data);

	if (errnum != 0)
		exit(errnum);
}

void	secondChild(t_info data, char **envp)
{
	int	errnum;

	errnum = 0;
	dup2(data.end[0], STDIN_FILENO);
	close(data.end[1]);
	dup2(data.fd_dst, STDOUT_FILENO);

	data.cmd = getCmdPath(data.cmd_path, data.cmd2_args[0]);
	if(!data.cmd)
	{
		errChild(ERR_CMD, data.cmd2_args[0]);
		errnum = 127;
	}
	else if (execve(data.cmd, data.cmd2_args, envp) == -1)
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
	if (data->cmd1_args)
	{
		while (data->cmd1_args[i++])
			free(data->cmd1_args[i]);
		free(data->cmd1_args);
	}
	i = 0;
	if (data->cmd2_args)
	{
		while (data->cmd2_args[i++])
			free(data->cmd2_args[i]);
		free(data->cmd2_args);
	}
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