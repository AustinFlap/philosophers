/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_simulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 22:39:24 by avieira           #+#    #+#             */
/*   Updated: 2021/10/10 14:40:35 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	*get_philo(int id, pthread_mutex_t *forks, int nb_philos)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = id;
	philo->nb_meal = 0;
	philo->left_fork = &forks[id];
	if (id != nb_philos - 1)
		philo->right_fork = &forks[id + 1];
	else
		philo->right_fork = &forks[0];
	return (philo);
}

void	create_simulation(t_simulation *simulation)
{
	int	i;

	simulation->philos = malloc(sizeof(t_philo *) * simulation->nb_philos);
	simulation->forks = malloc(sizeof(pthread_mutex_t) * simulation->nb_philos);
	if (!simulation->philos || !*simulation->philos || !simulation->forks)
		return ;//FREE
	i = -1;
	while (++i < simulation->nb_philos)
	{
		simulation->philos[i] = get_philo(i, simulation->forks, simulation->nb_philos);
		if (!simulation->philos[i])
			return ;//FREE
		pthread_mutex_init(&simulation->forks[i], NULL); 
	}
	i = -1;
	//while (++i < simulation->nb_philos)
	//	pthread_create(simulation->philos[i], NULL, -----, forks); 
}
