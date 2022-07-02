/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 15:33:28 by anarodri          #+#    #+#             */
/*   Updated: 2021/10/04 17:16:40 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Copies n bytes from src to dst using a temp array to handle overlap.
Return: original value of dst.
*/

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char	*str_dst;
	char	*str_src;

	str_dst = (char *)dst;
	str_src = (char *)src;
	if (str_dst == 0 && str_src == 0)
		return (0);
	while (n-- > 0)
	{
		if (str_dst > str_src)
			str_dst[n] = str_src[n];
		else
			*str_dst++ = *str_src++;
	}
	return (dst);
}
