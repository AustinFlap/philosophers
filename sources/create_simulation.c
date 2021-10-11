/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_simulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 22:39:24 by avieira           #+#    #+#             */
/*   Updated: 2021/10/11 20:25:16 by avieira          ###   ########.fr       */
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
	philo->nb_eat = 0;
	philo->left_fork = &forks[id - 1];
	if (id != nb_philos - 1)
		philo->right_fork = &forks[id];
	else
		philo->right_fork = &forks[0];
	return (philo);
}

void	create_simulation(t_simulation *simulation)
{
	int	i;
	pthread_mutex_t lock;

	simulation->philos = malloc(sizeof(t_philo *) * simulation->nb_philos);
	simulation->forks = malloc(sizeof(pthread_mutex_t) * simulation->nb_philos);
	if (!simulation->philos || !simulation->forks)
		return ;//FREE
	i = -1;
	pthread_mutex_init(&lock, NULL);
	while (++i < simulation->nb_philos)
	{
		simulation->philos[i] = get_philo(i + 1, simulation->forks, simulation->nb_philos);
		if (!simulation->philos[i])
			return ;//FREE
		simulation->philos[i]->lock = &lock;
		simulation->philos[i]->time_to_eat = simulation->time_to_eat;
		simulation->philos[i]->time_to_sleep = simulation->time_to_sleep;
		simulation->philos[i]->time_to_die = simulation->time_to_die;
		pthread_mutex_init(&simulation->forks[i], NULL); 
	}
}

void	destroy_simulation(t_simulation *simulation)
{
	int	i;

	i = -1;
	while (++i < simulation->nb_philos)
		free(simulation->philos[i]);
	free(simulation->forks);
	free(simulation->philos);
}
