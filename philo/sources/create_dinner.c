/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_dinner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 22:39:24 by avieira           #+#    #+#             */
/*   Updated: 2021/10/26 04:39:31 by avieira          ###   ########.fr       */
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
	philo->satisfaction = 0;
	if (id % 2)
	{
		philo->right_fork = &forks[id - 1];
		if (id == nb_philos)
			philo->left_fork = &forks[0];
		else
			philo->left_fork = &forks[id];
	}
	else
	{
		philo->left_fork = &forks[id - 1];
		if (id == nb_philos)
			philo->right_fork = &forks[0];
		else
			philo->right_fork = &forks[id];
	}
	return (philo);
}

void	set_info(t_dinner *dinner, int i)
{
	dinner->philos[i]->nb_philos = dinner->nb_philos;
	dinner->philos[i]->dinning = &dinner->dinning;
	dinner->philos[i]->lock = &dinner->lock;
	dinner->philos[i]->lock_print = &dinner->lock_print;
	dinner->philos[i]->lock_time = &dinner->lock_time;
	dinner->philos[i]->lock_dinning = &dinner->lock_dinning;
	dinner->philos[i]->time_to_eat = dinner->time_to_eat;
	dinner->philos[i]->time_to_sleep = dinner->time_to_sleep;
	dinner->philos[i]->time_to_die = dinner->time_to_die;
	dinner->philos[i]->nb_mandatory_eats = dinner->nb_mandatory_eats;
}

int	set_philos(t_dinner *dinner)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < dinner->nb_philos)
	{
		dinner->philos[i] = get_philo(i + 1, dinner->forks, dinner->nb_philos);
		if (!dinner->philos[i])
		{
			while (++j < i)
			{
				pthread_mutex_destroy(&dinner->forks[j]);
				free(dinner->philos[i]);
			}
			free(dinner->philos);
			free(dinner->forks);
			return (1);
		}
		set_info(dinner, i);
		pthread_mutex_init(&dinner->forks[i], NULL);
	}
	return (0);
}

int	create_dinner(t_dinner *dinner)
{
	dinner->philos = malloc(sizeof(t_philo *) * dinner->nb_philos);
	if (!dinner->philos)
		return (1);
	dinner->forks = malloc(sizeof(pthread_mutex_t) * dinner->nb_philos);
	if (!dinner->forks)
	{
		free(dinner->philos);
		return (1);
	}
	dinner->dinning = 0;
	if (set_philos(dinner))
		return (1);
	pthread_mutex_init(&dinner->lock, NULL);
	pthread_mutex_init(&dinner->lock_print, NULL);
	pthread_mutex_init(&dinner->lock_time, NULL);
	pthread_mutex_init(&dinner->lock_dinning, NULL);
	return (0);
}

void	destroy_dinner(t_dinner *dinner)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&dinner->lock);
	pthread_mutex_destroy(&dinner->lock_print);
	pthread_mutex_destroy(&dinner->lock_time);
	pthread_mutex_destroy(&dinner->lock_dinning);
	while (++i < dinner->nb_philos)
	{
		pthread_mutex_destroy(&dinner->forks[i]);
		free(dinner->philos[i]);
	}
	free(dinner->forks);
	free(dinner->philos);
}
