/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 21:03:39 by avieira           #+#    #+#             */
/*   Updated: 2021/10/26 04:26:50 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	death_test(t_philo *philo, pthread_mutex_t *r_f, pthread_mutex_t *l_f)
{
	if (get_dinning(philo))
	{
		if (r_f)
			pthread_mutex_unlock(r_f);
		if (l_f && r_f != l_f)
			pthread_mutex_unlock(l_f);
		pthread_mutex_unlock(philo->lock);
		return (1);
	}
	else if (l_f == r_f)
	{
		while (ms_since(&philo->last_eat, philo->lock_time)
			< (unsigned int)philo->time_to_die)
			usleep_ms(1, philo, NULL);
		print_msg(philo, " died\n", philo->lock_print);
		set_no_dinning(philo->dinning, philo->lock_dinning);
		pthread_mutex_unlock(philo->lock);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	return (0);
}

void	philo_eat(t_philo *philo)
{	
	pthread_mutex_lock(philo->lock_print);
	pthread_mutex_unlock(philo->lock_print);
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
	print_msg(philo, " is eating\n", philo->lock_print);
	get_time(&philo->last_eat, philo->lock_time);
	usleep_ms(philo->time_to_eat, philo, NULL);
	pthread_mutex_unlock(philo->lock);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo->nb_eat++;
}

void	philo_sleep(t_philo *philo)
{
	print_msg(philo, " is sleeping\n", philo->lock_print);
	gettimeofday(&philo->end_eat, NULL);
	usleep_ms(philo->time_to_sleep, philo, NULL);
}

void	philo_think(t_philo *philo)
{
	print_msg(philo, " is thinking\n", philo->lock_print);
}

void	*live(void *p_philo)
{
	t_philo	*philo;

	philo = p_philo;
	while (!get_dinning(philo) && eval_meal(philo))
	{
		if (!get_dinning(philo) && eval_meal(philo))
			philo_eat(philo);
		if (!get_dinning(philo) && eval_meal(philo))
			philo_sleep(philo);
		if (!get_dinning(philo) && eval_meal(philo))
			philo_think(philo);
		if (philo->nb_philos % 2
			&& (int)ms_since(&philo->last_eat, philo->lock_time)
			+ philo->time_to_eat < philo->time_to_die)
			usleep_ms(philo->time_to_eat, philo, NULL);
	}
	if (!eval_meal(philo))
		set_yes_satisfaction(philo);
	return (NULL);
}
