/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 14:45:53 by avieira           #+#    #+#             */
/*   Updated: 2021/10/14 12:58:37 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->lock);
	pthread_mutex_lock(philo->left_fork);
	print_msg(philo, " has taken a fork\n", NULL);
	pthread_mutex_lock(philo->right_fork);
	*philo->eating = 1;
	print_msg(philo, " has taken a fork\n", NULL);
	print_msg(philo, " is eating\n", NULL);
	pthread_mutex_unlock(philo->lock);
	usleep_ms(philo->time_to_eat);
	philo->nb_eat++;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	gettimeofday(&philo->last_eat, NULL);
	*philo->eating = 0;
}

void	philo_sleep(t_philo *philo)
{
	print_msg(philo, " is sleeping\n", philo->lock);
	usleep_ms(philo->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	print_msg(philo, " is thinking\n", philo->lock);
}

void	*observer(void *p_philo)
{
	t_philo *philo;

	philo = p_philo;
	while (!*philo->end)
	{
		if (ms_since(philo->last_eat) > (unsigned int)philo->time_to_die && !*philo->eating)
		{
			*philo->end = 1;
			print_msg(philo, " died\n", philo->lock);
		}
		usleep(1000);
	}
	return (NULL);
}

void	*live(void *p_philo)
{
	t_philo	*philo;
	pthread_t obs_thread;

	philo = p_philo;
	pthread_create(&obs_thread, NULL, observer, philo);
	pthread_detach(obs_thread);
	while (!*philo->end)
	{
		if (!*philo->end)
			philo_eat(philo);
		if (!*philo->end)
			philo_sleep(philo);
		if (!*philo->end)
			philo_think(philo);
	}
	return (NULL);
}

void	launch_simulation(t_simulation *simulation)
{
	int	i;

	gettimeofday(&simulation->start, NULL);
	i = -1;
	while (++i < simulation->nb_philos)
	{
		simulation->philos[i]->birth = &simulation->start;
		simulation->philos[i]->last_eat = simulation->start;
		pthread_create(&simulation->philos[i]->thread, NULL, live, simulation->philos[i]);
	}
	i = -1;
	while (++i < simulation->nb_philos)
		pthread_join(simulation->philos[i]->thread, NULL);
}
