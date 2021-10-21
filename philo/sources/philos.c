/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 21:03:39 by avieira           #+#    #+#             */
/*   Updated: 2021/10/21 11:27:18 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	death_test(t_philo *philo, pthread_mutex_t *right_fork, pthread_mutex_t *left_fork)
{
	if (*philo->dinning)
	{
		if (right_fork)
			pthread_mutex_unlock(right_fork);
		if (left_fork && right_fork != left_fork)
			pthread_mutex_unlock(left_fork);
		pthread_mutex_unlock(philo->lock);
		return (1);
	}
	else if (left_fork == right_fork)
	{
		*philo->dinning = 1;
		while (ms_since(philo->last_eat) < (unsigned int)philo->time_to_die)
			usleep_ms(1, philo, NULL);
		print_msg(philo, " died\n", philo->lock_print);
		return (1);
	}
	return (0);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->lock);
	pthread_mutex_lock(philo->right_fork);
	if (death_test(philo, philo->right_fork, NULL))
		return ;
	print_msg(philo, " has taken a fork\n", philo->lock_print);
	if (philo->right_fork != philo->left_fork)
		pthread_mutex_lock(philo->left_fork);
	if (death_test(philo, philo->right_fork, philo->left_fork))
		return ;
	print_msg(philo, " has taken a fork\n", philo->lock_print);
	*philo->action = eating;
	print_msg(philo, " is eating\n", philo->lock_print);
	gettimeofday(&philo->last_eat, NULL);
	pthread_mutex_unlock(philo->lock);
	usleep_ms(philo->time_to_eat, philo, &philo->last_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	gettimeofday(&philo->end_eat, NULL);
	philo->nb_eat++;
}

void	philo_sleep(t_philo *philo)
{
	*philo->action = sleeping;
	print_msg(philo, " is sleeping\n", philo->lock_print);
	usleep_ms(philo->time_to_sleep, philo, &philo->end_eat);
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
	while (!*philo->dinning && eval_meal(philo))
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
