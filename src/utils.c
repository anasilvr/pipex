/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 11:48:28 by anarodri          #+#    #+#             */
/*   Updated: 2022/07/06 18:16:47 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	init_struct(t_info *data)
{
	data->envp_path = NULL;
	data->cmd = NULL;
	data->cmd_path = NULL;
	data->cmd_args = NULL;
	data->status = 0;
}

char	*search_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

void	parse_envp(char **envp, t_info *data)
{
	data->envp_path = search_path(envp);
	data->cmd_path = ft_split(data->envp_path, ':');
}

char	*get_cmdpath(char **cmd_path, char *cmd)
{
	char	*tmp;
	char	*res;
	int		i;

	i = 0;
	if (!cmd)
		return (NULL);
	while (cmd && cmd[i])
	{
		if (cmd[0] == '.' || cmd [i] == '/')
			return (ft_strdup(cmd));
		i++;
	}
	while (*cmd_path)
	{
		tmp = ft_strjoin(*cmd_path, "/");
		res = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(res, 0) == 0)
			return (res);
		free(res);
		cmd_path++;
	}
	free(cmd);
	return (NULL);
}
