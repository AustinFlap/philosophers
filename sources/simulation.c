/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 14:45:53 by avieira           #+#    #+#             */
/*   Updated: 2021/10/11 17:47:22 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*live(void *philo)
{
	t_philo	*hehe;
	hehe = philo;
	printf("philo %d woke up\n", hehe->id);
	return (NULL);
}

void	launch_simulation(t_simulation *simulation)
{
	int	i;

	i = -1;
	while (++i < simulation->nb_philos)
		pthread_create(&simulation->philos[i]->thread, NULL, live, simulation->philos[i]);
	i = -1;
	while (++i < simulation->nb_philos)
		pthread_join(simulation->philos[i]->thread, NULL);
}
