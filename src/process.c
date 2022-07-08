/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 11:48:25 by anarodri          #+#    #+#             */
/*   Updated: 2022/07/08 17:33:24 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	first_child(t_info data, char **argv, char **envp)
{
	int	errnum;

	errnum = 0;
	dup2(data.end[1], STDOUT_FILENO);
	close(data.end[0]);
	dup2(data.fd_src, STDIN_FILENO);
	data.cmd_args = ft_split(argv[2], ' ');
	data.cmd = get_cmdpath(data.cmd_path, data.cmd_args[0]);
	if (!data.cmd)
	{
		err_child(data.cmd_args[0], ERR_CMD);
		errnum = 127;
	}
	else if (execve(data.cmd, data.cmd_args, envp) == -1)
	{
		err_child(data.cmd, ERR_CMD);
		errnum = 127;
	}
	if (errnum != 0)
	{
		free_childfail(&data);
		exit(errnum);
	}
	else
		free_child(&data);
}

void	second_child(t_info data, char **argv, char **envp)
{
	int	errnum;

	errnum = 0;
	dup2(data.end[0], STDIN_FILENO);
	close(data.end[1]);
	dup2(data.fd_dst, STDOUT_FILENO);
	data.cmd_args = ft_split(argv[3], ' ');
	data.cmd = get_cmdpath(data.cmd_path, data.cmd_args[0]);
	if (!data.cmd)
	{
		err_child(data.cmd_args[0], ERR_CMD);
		errnum = 127;
	}
	else if (execve(data.cmd, data.cmd_args, envp) == -1)
	{
		err_child(data.cmd, ERR_CMD);
		errnum = 127;
	}
	if (errnum != 0)
	{
		free_childfail(&data);
		exit(errnum);
	}
	else
		free_child(&data);
}
