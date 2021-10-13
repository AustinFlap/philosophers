/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 14:45:53 by avieira           #+#    #+#             */
/*   Updated: 2021/10/13 03:53:10 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_eat(t_philo *philo)
{

	pthread_mutex_lock(philo->lock);
	pthread_mutex_lock(philo->left_fork);
	print_msg(philo->id, " has taken a fork\n", NULL);
	pthread_mutex_lock(philo->right_fork);
	print_msg(philo->id, " has taken a fork\n", NULL);
	print_msg(philo->id, " is eating\n", NULL);
	pthread_mutex_unlock(philo->lock);
	usleep_ms(philo->time_to_eat);
	philo->nb_eat++;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_sleep(t_philo *philo)
{
	print_msg(philo->id, " is sleeping\n", philo->lock);
	usleep_ms(philo->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	print_msg(philo->id, " is thinking\n", philo->lock);
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
	{
		//usleep(10);
		pthread_create(&simulation->philos[i]->thread, NULL, live, simulation->philos[i]);
	}
	i = -1;
	while (++i < simulation->nb_philos)
		pthread_join(simulation->philos[i]->thread, NULL);
}
