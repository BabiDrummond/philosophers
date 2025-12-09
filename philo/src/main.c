/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:41:52 by bmoreira          #+#    #+#             */
/*   Updated: 2025/12/09 17:36:20 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int kill_philos(t_table *table)
{
	int	i;
	
	i = -1;
	while (++i < table->num_philos)
		if (pthread_join(table->philos[i].thread_id, NULL))
			return (throw_error(table, table->num_philos, "Thread joining"));
	return (TRUE);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (!validate_input(argc, argv))
		return (EXIT_FAILURE);
	if (!init_data(&table, argc, argv))
		return (EXIT_FAILURE);
	// start routine contem a logica do projeto (pegar garfos, comer, dormir)
	// monitor contem logica de controle da simulação (filósofos estão vivos? deve continuar rodando?)
	start_monitor(&table);
	if (!kill_philos(&table))
		return (EXIT_FAILURE);
	clean_all(&table, table.num_philos);
	return (EXIT_SUCCESS);
}
