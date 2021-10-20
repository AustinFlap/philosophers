/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_dinner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 22:39:24 by avieira           #+#    #+#             */
/*   Updated: 2021/10/20 22:12:17 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	*get_philo(int id, pthread_mutex_t *forks, int nb_philos)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	philo->action = malloc(sizeof(t_action));
	if (!philo || !philo->action)
		return (NULL);
	philo->id = id;
	philo->nb_eat = 0;
	philo->left_fork = &forks[id - 1];
	*philo->action = thinking;
	if (id != nb_philos)
		philo->right_fork = &forks[id];
	else
		philo->right_fork = &forks[0];
	return (philo);
}

void	create_dinner(t_dinner *dinner)
{
	int	i;

	dinner->philos = malloc(sizeof(t_philo *) * dinner->nb_philos);
	dinner->forks = malloc(sizeof(pthread_mutex_t) * dinner->nb_philos);
	if (!dinner->philos || !dinner->forks)
		return ;//FREE
	dinner->dinning = 0;
	i = -1;
	while (++i < dinner->nb_philos)
	{
		dinner->philos[i] = get_philo(i + 1, dinner->forks, dinner->nb_philos);
		if (!dinner->philos[i])
			return ;//FREE
		dinner->philos[i]->dinning = &dinner->dinning;
		dinner->philos[i]->lock = &dinner->lock;
		dinner->philos[i]->lock_print = &dinner->lock_print;
		dinner->philos[i]->time_to_eat = dinner->time_to_eat;
		dinner->philos[i]->time_to_sleep = dinner->time_to_sleep;
		dinner->philos[i]->time_to_die = dinner->time_to_die;
		pthread_mutex_init(&dinner->forks[i], NULL); 
	}
	pthread_mutex_init(&dinner->lock, NULL);
}

void	destroy_dinner(t_dinner *dinner)
{
	int	i;

	i = -1;
	while (++i < dinner->nb_philos)
		free(dinner->philos[i]);
	free(dinner->forks);
	free(dinner->philos);
}
