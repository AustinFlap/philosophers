/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 21:03:39 by avieira           #+#    #+#             */
/*   Updated: 2021/10/20 22:30:47 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	death_test(t_philo *philo, pthread_mutex_t *left_fork, pthread_mutex_t *right_fork)
{
	if (*philo->dinning)
	{
		if (left_fork)
			pthread_mutex_unlock(left_fork);
		if (right_fork)
			pthread_mutex_unlock(right_fork);
		pthread_mutex_unlock(philo->lock);
		return (1);
	}
	return (0);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->lock);
	pthread_mutex_lock(philo->left_fork);
	if (death_test(philo, philo->left_fork, NULL))
		return ;
	print_msg(philo, " has taken a fork\n", philo->lock_print);
	pthread_mutex_lock(philo->right_fork);
	if (death_test(philo, philo->left_fork, philo->right_fork))
		return ;
	print_msg(philo, " has taken a fork\n", philo->lock_print);
	*philo->action = eating;
	print_msg(philo, " is eating\n", philo->lock_print);
	pthread_mutex_unlock(philo->lock);
	usleep_ms(philo->time_to_eat, philo);
	philo->nb_eat++;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	gettimeofday(&philo->last_eat, NULL);
}

void	philo_sleep(t_philo *philo)
{
	print_msg(philo, " is sleeping\n", philo->lock_print);
	*philo->action = sleeping;
	usleep_ms(philo->time_to_sleep, philo);
}

void	philo_think(t_philo *philo)
{
	print_msg(philo, " is thinking\n", philo->lock_print);
	*philo->action = thinking;
}

void	*live(void *p_philo)
{
	t_philo	*philo;
	pthread_t	obs;

	philo = p_philo;
	pthread_create(&obs, NULL, observer, p_philo);
	pthread_detach(obs);
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
