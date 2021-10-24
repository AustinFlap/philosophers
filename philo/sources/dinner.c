/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 14:45:53 by avieira           #+#    #+#             */
/*   Updated: 2021/10/24 14:22:44 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*observer(void *p_dinner)
{
	int i;
	t_dinner *dinner;
	t_philo *philo;

	dinner = p_dinner;
	while (!dinner->dinning)
	{
		i = -1;
		while (!dinner->dinning && ++i < dinner->nb_philos)
		{
			philo = dinner->philos[i];
			if (ms_since(philo->last_eat) > (unsigned int)philo->time_to_die && *philo->action != eating && !*philo->dinning)
			{
				pthread_mutex_lock(philo->lock);
				print_msg(philo, " died\n", philo->lock_print);
				*philo->dinning = 1;
				pthread_mutex_unlock(philo->lock);
			}
			usleep(1);
		}
	}
	return (NULL);
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
	pthread_detach(obs);
	i = -1;
	while (++i < dinner->nb_philos)
		pthread_join(dinner->philos[i]->thread, NULL);
}
