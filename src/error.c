/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 18:01:43 by anarodri          #+#    #+#             */
/*   Updated: 2022/07/06 18:15:40 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	err_msg(const char *msg, int n)
{
	perror(msg);
	exit(n);
}

void	err_child(const char *msg, char *arg)
{
	write(2, msg, ft_strlen(msg));
	write(2, arg, ft_strlen(arg));
	write(2, "\n", 1);
}
