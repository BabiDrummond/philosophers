/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:41:52 by bmoreira          #+#    #+#             */
/*   Updated: 2025/12/09 20:38:45 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_table	table;
	int		status;

	status = EXIT_SUCCESS;
	if (!validate_input(argc, argv))
		status = EXIT_FAILURE;
	if (!init_data(&table, argc, argv))
		status = EXIT_FAILURE;
	// start routine contem a logica do projeto (pegar garfos, comer, dormir)
	// monitor contem logica de controle da simulação (filósofos estão vivos? deve continuar rodando?)
	start_monitor(&table);
	if (!destroy_data(&table))
		status = EXIT_FAILURE;
	return (EXIT_SUCCESS);
}
