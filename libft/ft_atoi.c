/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 13:26:51 by anarodri          #+#    #+#             */
/*   Updated: 2021/10/25 11:57:08 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Converts ASCII string to integer.
The atoi function skips all white-space characters,
converts the subsequent characters as part of the number,
and then stops when it encounters the first character that isn't a number.
If no valid conversion could be performed, it returns zero.
*/

#include "libft.h"

int	ft_atoi(const char *str)
{
	long	nbr;
	int		i;
	int		neg;

	i = 0;
	neg = 1;
	nbr = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-')
		neg *= -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = (nbr * 10) + str[i] - '0';
		i++;
		if (nbr * neg > INT_MAX)
			return (-1);
		if (nbr * neg < INT_MIN)
			return (0);
	}
	return (nbr * neg);
}
