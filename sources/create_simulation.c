/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_simulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 22:39:24 by avieira           #+#    #+#             */
/*   Updated: 2021/10/07 23:34:27 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void				create_simulation(t_simulation *simulation)
{
	int				i;

	if (!(*simulation->philos = malloc(sizeof(t_philo *) * simulation->nb_philos)))
		return ;
	if (!(simulation->forks = malloc(sizeof(pthread_mutex_t) * simulation->nb_philos)))
		return ;
	i = -1;
	while (++i < simulation->nb_philos)
		pthread_mutex_init(forks[i], NULL); 
	i = -1;
	while (++i < simulation->nb_philos)
		pthread_create(philos[i], NULL, -----, forks); 
}
