/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 14:45:53 by avieira           #+#    #+#             */
/*   Updated: 2021/10/10 15:01:36 by avieira          ###   ########.fr       */
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
	printf("Before launch\n");
	while (i < simulation->nb_philos)
		pthread_create(&(simulation->philos[i]->thread), NULL, &live, simulation->philos[i]);
	printf("After launch\n");
}
