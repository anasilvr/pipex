/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 11:48:36 by anarodri          #+#    #+#             */
/*   Updated: 2022/07/08 17:57:01 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 For the shell’s purposes:
 A command which exits with a zero exit status has succeeded.
 A non-zero exit status indicates failure.

 Command is not found: the child process created returns 127.
 Command is found but is not executable: returns 126.
 Command fails because of an error during expansion or redirection: returns > 0.
 */

#ifndef PIPEX_H
# define PIPEX_H

# define ERR_ARGC "Invalid number of arguments"
//# define ERR_OPEN "Open() funtion failed."
# define ERR_PIPE ": unable to create a pipe"
# define ERR_CMD ": command not found"
# define ERR_OPEN ": no such file or directory"

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>

# include "../libft/libft.h"

typedef struct s_info
{
	int		fd_src;
	int		fd_dst;
	int		valid_file;
	int		end[2];
	char	*envp_path;
	char	*cmd;
	char	**cmd_path;
	char	**cmd_args;
	pid_t	child1;
	pid_t	child2;
	int		status;
}	t_info;

char	*search_path(char **envp);
char	*get_cmdpath(char **cmd_path, char *cmd);

void	open_filefd(t_info *data, char **argv);
void	init_struct(t_info *data);
void	parse_envp(char **envp, t_info *data);
int		init_pipex(t_info *data, char **argv, char **envp);
void	first_child(t_info data, char **argv, char **envp);
void	second_child(t_info data, char **argv, char **envp);

void	free_struct(t_info *data);
void	free_2darray(char **arr);
void	free_child(t_info *data);
void	free_parent(t_info *data);
void	free_childfail(t_info *data);

void	err_msg(const char *msg, int n);
void	err_child(const char *msg, char *arg);

#endif