/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 11:48:28 by anarodri          #+#    #+#             */
/*   Updated: 2022/07/03 21:24:16 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	errMsg(const char *msg, int n)
{
	perror(msg);
	exit(n);
}

void	errChild(const char *msg, char *arg)
{
	write(2, msg, ft_strlen(msg));
	write(2, arg, ft_strlen(arg));
	write(2, "\n", 1);
}

char	*searchPath(char **envp)
{
	while (ft_strncmp(*envp, "PATH=", 5))
		envp++;
	return (*envp + 5);
}

void	parseEnvp(char **envp, t_info *data)
{
	data->envp_PATH = searchPath(envp);
	data->cmd_path = ft_split(data->envp_PATH, ':');
//	data->cmd1_args = ft_split(argv[2], ' ');
//	data->cmd2_args = ft_split(argv[3], ' ');
}

char	*getCmdPath (char **cmd_path, char *cmd)
{
	char	*tmp;
	char	*res;
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[0] == '.'|| cmd [i] == '/')
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
	return (NULL);
}