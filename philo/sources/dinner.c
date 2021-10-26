/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 14:45:53 by avieira           #+#    #+#             */
/*   Updated: 2021/10/26 05:54:24 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*observer(void *p_dinner)
{
	int			i;
	t_dinner	*dinner;
	t_philo		*philo;
	int			n_satisfied;

	dinner = p_dinner;
	while (!get_dinning(dinner->philos[0]))
	{
		i = -1;
		n_satisfied = 0;
		while (!get_dinning(dinner->philos[0]) && ++i < dinner->nb_philos)
		{
			philo = dinner->philos[i];
			if (ms_since(&philo->last_eat, philo->lock_time)
				>= (unsigned int)philo->time_to_die && !get_dinning(philo))
			{
				pthread_mutex_lock(philo->lock_print);
				print_msg(philo, " died\n", NULL);
				set_no_dinning(philo->dinning, philo->lock_dinning);
				pthread_mutex_unlock(philo->lock_print);
				return (NULL);
			}
			else if (get_satisfaction(philo))
				n_satisfied++;
			if (n_satisfied == dinner->nb_philos)
				set_no_dinning(philo->dinning, philo->lock_dinning);
			usleep(1);
		}
	}
	return (NULL);
}

void	launch_philos(t_dinner *d)
{
	int	i;

	i = 1;
	while (i < d->nb_philos)
	{
		d->philos[i]->birth = d->start;
		d->philos[i]->last_eat = d->start;
		pthread_create(&d->philos[i]->thread, NULL, live, d->philos[i]);
		i += 2;
	}
	usleep(500);
	i = 0;
	while (i < d->nb_philos)
	{
		d->philos[i]->birth = d->start;
		d->philos[i]->last_eat = d->start;
		pthread_create(&d->philos[i]->thread, NULL, live, d->philos[i]);
		i += 2;
	}
}

void	launch_dinner(t_dinner *d)
{
	int			i;
	pthread_t	obs;

	i = 1;
	gettimeofday(&d->start, NULL);
	launch_philos(d);
	pthread_create(&obs, NULL, observer, d);
	i = -1;
	while (++i < d->nb_philos)
		pthread_join(d->philos[i]->thread, NULL);
	set_no_dinning(&d->dinning, &d->lock_dinning);
	pthread_join(obs, NULL);
}
