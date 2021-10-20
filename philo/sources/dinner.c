/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 14:45:53 by avieira           #+#    #+#             */
/*   Updated: 2021/10/20 22:26:40 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*observer(void *p_philo)
{
	t_philo	*philo;

	philo = p_philo;
	while (!*philo->dinning)
	{
		if (ms_since(philo->last_eat) > (unsigned int)philo->time_to_die && *philo->action != eating && !*philo->dinning)
		{
			//printf("%d philo : %d last_eat was %u ms ago\n", ms_since(philo->birth), philo->id, ms_since(philo->last_eat));
			*philo->dinning = 1;
			print_msg(philo, " died\n", philo->lock_print);
		}
		usleep(500);
	}
	return (NULL);
}

void	launch_dinner(t_dinner *dinner)
{
	int	i;

	i = -1;
	gettimeofday(&dinner->start, NULL);
	while (++i < dinner->nb_philos)
	{
		dinner->philos[i]->birth = dinner->start;
		dinner->philos[i]->last_eat = dinner->start;
		pthread_create(&dinner->philos[i]->thread, NULL, live, dinner->philos[i]);
	}
	i = -1;
	while (++i < dinner->nb_philos)
		pthread_join(dinner->philos[i]->thread, NULL);
}
