/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_atoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 01:51:48 by bmoreira          #+#    #+#             */
/*   Updated: 2025/12/07 14:21:30 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	safe_atoi(char *str)
{
	long	num;
	int		negative;

	num = 0;
	negative = 1;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			negative *= -1;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return ((long) INT_MAX + 1);
		num = (num * 10) + *str++ - 48;
		if ((num > INT_MAX && negative == 1)
			|| (num > (long) INT_MAX + 1 && negative == -1))
			return ((long) INT_MAX + 1);
	}
	return (num * negative);
}
