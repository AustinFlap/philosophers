/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 21:03:39 by avieira           #+#    #+#             */
/*   Updated: 2021/10/18 22:18:35 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->lock);
	if (*philo->dinning)
	{
		pthread_mutex_unlock(philo->lock);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	if (*philo->dinning)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->lock);
		return ;
	}
	print_msg(philo, " has taken a fork\n", NULL);
	pthread_mutex_lock(philo->right_fork);
	if (*philo->dinning)
	{
		pthread_mutex_unlock(philo->lock);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	print_msg(philo, " has taken a fork\n", NULL);
	*philo->action = eating;
	print_msg(philo, " is eating\n", NULL);
	pthread_mutex_unlock(philo->lock);
	usleep_ms(philo->time_to_eat);
	philo->nb_eat++;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	gettimeofday(&philo->last_eat, NULL);
}

void	philo_sleep(t_philo *philo)
{
	print_msg(philo, " is sleeping\n", philo->lock);
	*philo->action = sleeping;
	usleep_ms(philo->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	print_msg(philo, " is thinking\n", philo->lock);
	*philo->action = thinking;
}

void	*live(void *p_philo)
{
	t_philo	*philo;
	pthread_t	obs;

	philo = p_philo;
	pthread_create(&obs, NULL, observer, p_philo);
	while (!*philo->dinning)
	{
		if (!*philo->dinning)
			philo_eat(philo);
		if (!*philo->dinning)
			philo_sleep(philo);
		if (!*philo->dinning)
			philo_think(philo);
	}
	return (NULL);
}
