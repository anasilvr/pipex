/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 11:48:28 by anarodri          #+#    #+#             */
/*   Updated: 2022/07/19 15:43:46 by anarodri         ###   ########.fr       */
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
	int	i;

	i = 0;
	while (envp[i] != NULL && ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	if (envp[i] == NULL)
		return (NULL);
	else
		return (envp[i] + 5);
}

void	parse_envp(char **envp, t_info *data)
{
	int	i;

	i = 0;
	data->envp_path = search_path(envp);
	if (!data->envp_path)
	{
		free(data->envp_path);
		err_msg("ENVP not set. Restart your shell", 127);
	}
	else
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
		if (access(res, F_OK | X_OK) == 0)
			return (res);
		free(res);
		cmd_path++;
	}
	return (NULL);
}
