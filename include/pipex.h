/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 11:48:36 by anarodri          #+#    #+#             */
/*   Updated: 2022/07/02 14:45:17 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* For the shell’s purposes, a command which exits with a zero exit status has succeeded.
 A non-zero exit status indicates failure.
 If a command is not found, the child process created to execute it returns a status of 127.
 If a command is found but is not executable, the return status is 126.
 If a command fails because of an error during expansion or redirection,
 the exit status is greater than zero.
 */

#ifndef PIPEX_H
#define PIPEX_H

# define ERR_ARGC "Invalid number of arguments."
# define ERR_OPEN "Open() funtion failed."
# define ERR_PIPE ": unable to create a pipe"
# define ERR_CMD ": command not found"
# define ERR_EXEC ": no such file or directory"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>

#include "../libft/libft.h"

typedef struct s_info
{
	int		fd_src;
	int		fd_dst;
//	int		valid_file;
	int		end[2];
	char	*envp_PATH;
	char	*cmd;
	char	**cmd_path;
	char	**cmd1_args;
	char	**cmd2_args;
	pid_t	child1;
	pid_t	child2;
	int		status;
} 	t_info;


// void	getSrcFD(char *arg, t_info *input);
// void	getDstFD(char *arg, t_info *input);

char	*searchPath(char **envp);
char	*getCmdPath (char **cmd_path, char *cmd);

void	parseInput(char **argv, char **envp, t_info *data);
void	initPipex(t_info *data, char **envp);
void	firstChild(t_info data, char **envp);
void	secondChild(t_info data, char **envp);
void	freeChild(t_info *data);
void	freeParent(t_info *data);
void	errMsg(const char *msg, int n);
void	errChild(const char *msg, char *arg);

#endif