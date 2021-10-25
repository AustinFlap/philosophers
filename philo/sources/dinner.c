/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 14:45:53 by avieira           #+#    #+#             */
/*   Updated: 2021/10/26 00:19:59 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*observer(void *p_dinner)
{
	int i;
	t_dinner *dinner;
	t_philo *philo;

	dinner = p_dinner;
	while (!get_dinning(dinner->philos[0]))
	{
		i = -1;
		while (!get_dinning(dinner->philos[0]) && ++i < dinner->nb_philos)
		{
			philo = dinner->philos[i];
			if (ms_since(&philo->last_eat, philo->lock_time) > (unsigned int)philo->time_to_die && !get_dinning(philo) && !get_satisfaction(philo))
			{
				pthread_mutex_lock(philo->lock_print);
				print_msg(philo, " died\n", NULL);
				set_no_dinning(philo->dinning, philo->lock_dinning);
				pthread_mutex_unlock(philo->lock_print);
				return (NULL);
			}
			usleep(1);
		}
	}
	return (NULL);
}


void	set_yes_satisfaction(t_philo *philo)
{
	pthread_mutex_lock(philo->lock_dinning);
	philo->satisfaction = 1;
	pthread_mutex_unlock(philo->lock_dinning);
}

int	get_satisfaction(t_philo *philo)
{
	int tmp;

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
	int tmp;

	pthread_mutex_lock(philo->lock_dinning);
	tmp = *philo->dinning;
	pthread_mutex_unlock(philo->lock_dinning);
	return (tmp);
}

int		eval_meal(t_philo *philo)
{
	if (philo->nb_eat < philo->nb_mandatory_eats || philo->nb_mandatory_eats == -2)
		return (1);
	return (0);
}

void	launch_dinner(t_dinner *dinner)
{
	int	i;
	pthread_t obs;

	i = 1;
	gettimeofday(&dinner->start, NULL);
	while (i < dinner->nb_philos)
	{
		dinner->philos[i]->birth = dinner->start;
		dinner->philos[i]->last_eat = dinner->start;
		pthread_create(&dinner->philos[i]->thread, NULL, live, dinner->philos[i]);
		i += 2;
	}
	i = 0;
	usleep(500);
	while (i < dinner->nb_philos)
	{
		dinner->philos[i]->birth = dinner->start;
		dinner->philos[i]->last_eat = dinner->start;
		pthread_create(&dinner->philos[i]->thread, NULL, live, dinner->philos[i]);
		i += 2;
	}
	pthread_create(&obs, NULL, observer, dinner);
	i = -1;
	while (++i < dinner->nb_philos)
		pthread_join(dinner->philos[i]->thread, NULL);
	set_no_dinning(&dinner->dinning, &dinner->lock_dinning);
	pthread_join(obs, NULL);
}
