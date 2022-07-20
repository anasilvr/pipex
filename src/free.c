/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 12:09:16 by anarodri          #+#    #+#             */
/*   Updated: 2022/07/13 13:25:03 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_struct(t_info *s)
{
	if (s->envp_path)
		free(s->envp_path);
	if (s->cmd)
		free(s->cmd);
	if (s->cmd_args)
		free_2darray(s->cmd_args);
	if (s->cmd_path)
		free_2darray(s->cmd_path);
}

void	free_2darray(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_child(t_info *data)
{
	int	i;

	i = 0;
	if (data->cmd_args)
	{
		while (data->cmd_args[i])
		{
			free(data->cmd_args[i]);
			i++;
		}
		free(data->cmd_args);
	}
	if (data->cmd)
		free(data->cmd);
}

void	free_parent(t_info *data)
{
	int	i;

	i = 0;
	if (data->cmd_path)
	{
		while (data->cmd_path[i])
		{
			free(data->cmd_path[i]);
			i++;
		}
		free(data->cmd_path);
	}
	close(data->fd_src);
	close(data->fd_dst);
}

void	free_childfail(t_info *data)
{
	int	i;

	i = 0;
	if (data->cmd_path)
	{
		while (data->cmd_path[i])
		{
			free(data->cmd_path[i]);
			data->cmd_path[i] = NULL;
			i++;
		}
		free (data->cmd_path);
		data->cmd_path = NULL;
	}
	free_child(data);
}
