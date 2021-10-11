/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 14:45:53 by avieira           #+#    #+#             */
/*   Updated: 2021/10/11 20:32:43 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_eat(t_philo *philo)
{
	//pthread_mutex_lock(philo->lock);
	pthread_mutex_lock(philo->left_fork);
	printf("%d has taken a fork\n", philo->id);
	pthread_mutex_lock(philo->right_fork);
	printf("%d has taken a fork\n", philo->id);
	//pthread_mutex_unlock(philo->lock);
	printf("%d is eating\n", philo->id);
	usleep_ms(philo->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo->nb_eat++;
}

void	philo_sleep(t_philo *philo)
{
	printf("%d is sleeping\n", philo->id);
	usleep_ms(philo->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	printf("%d is thinking\n", philo->id);
}

void	*live(void *p_philo)
{
	t_philo	*philo;

	philo = p_philo;
	while (1)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
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
