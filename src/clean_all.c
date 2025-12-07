/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 22:29:15 by bmoreira          #+#    #+#             */
/*   Updated: 2025/12/06 22:32:13 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clean_all(t_table *table, int m_count)
{
	int	i;

	i = -1;
	while (++i < m_count)
		pthread_mutex_destroy(&table->philos[i].fork_r);
	if (table && table->philos)
		free(table->philos);
}
