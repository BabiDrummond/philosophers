/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 01:52:48 by bmoreira          #+#    #+#             */
/*   Updated: 2025/12/07 18:58:22 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	throw_error(t_table *table, int m_count, const char *msg)
{
	printf("Error: %s.\n", msg);
	clean_all(table, m_count);
	return (FALSE);
}
