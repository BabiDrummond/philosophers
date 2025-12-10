/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:41:52 by bmoreira          #+#    #+#             */
/*   Updated: 2025/12/10 00:27:58 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	destroy_data(&table, table.num_philos, table.num_philos);
	return (EXIT_SUCCESS);
}
