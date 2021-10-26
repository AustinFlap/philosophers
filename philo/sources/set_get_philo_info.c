/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_get_philo_info.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 02:59:53 by avieira           #+#    #+#             */
/*   Updated: 2021/10/26 05:19:47 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	set_yes_satisfaction(t_philo *philo)
{
	pthread_mutex_lock(philo->lock_dinning);
	philo->satisfaction = 1;
	pthread_mutex_unlock(philo->lock_dinning);
}

int	get_satisfaction(t_philo *philo)
{
	int	tmp;

	pthread_mutex_lock(philo->lock_dinning);
	tmp = philo->satisfaction;
	pthread_mutex_unlock(philo->lock_dinning);
	return (tmp);
}

void	set_no_dinning(int *dinning, pthread_mutex_t *lock)
{
	pthread_mutex_lock(lock);
	*dinning = 1;
	pthread_mutex_unlock(lock);
}

int	get_dinning(t_philo *philo)
{
	int	tmp;

	pthread_mutex_lock(philo->lock_dinning);
	tmp = *philo->dinning;
	pthread_mutex_unlock(philo->lock_dinning);
	return (tmp);
}

int	eval_meal(t_philo *philo)
{
	if (philo->nb_eat < philo->nb_mandatory_eats
		|| philo->nb_mandatory_eats == -2)
		return (1);
	set_yes_satisfaction(philo);
	return (0);
}
