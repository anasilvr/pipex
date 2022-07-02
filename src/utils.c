/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 11:48:28 by anarodri          #+#    #+#             */
/*   Updated: 2022/07/02 15:01:05 by anarodri         ###   ########.fr       */
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
// void	getSrcFD(char *arg, t_info *input)
// {
// 	input->fd_src = open(arg, O_RDONLY);
// 	if (input->fd_src < 0)
// 		perror(ERR_OPEN);
// 		// {
// 		// 	perror(arg);
// 		// 	input->valid_file = 0;
// 		// else
// 		// 	input->valid_file = 1;
// }

// void	getDstFD(char *arg, t_info *input)
// {
// 	input->fd_dst = open(arg, O_CREAT | O_RDWR | O_TRUNC, 0644);
// 	if (input->fd_dst < 0)
// 		perror(ERR_OPEN);
// }

char	*searchPath(char **envp)
{
	while (ft_strncmp(*envp, "PATH=", 5))
		envp++;
	return (*envp + 5);
}

void	parseInput(char **argv, char **envp, t_info *data)
{
	data->envp_PATH = searchPath(envp);
	data->cmd_path = ft_split(data->envp_PATH, ':');
	data->cmd1_args = ft_split(argv[2], ' ');
	data->cmd2_args = ft_split(argv[3], ' ');
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