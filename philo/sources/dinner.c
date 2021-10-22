/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 14:45:53 by avieira           #+#    #+#             */
/*   Updated: 2021/10/22 14:42:32 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	observer(t_dinner *dinner)
{
	int i;
	t_philo *philo;

	i = -1;
	while (!dinner->dinning && ++i < dinner->nb_philos)
	{
		philo = dinner->philos[i];
		if (ms_since(philo->last_eat) > (unsigned int)philo->time_to_die && *philo->action != eating && !*philo->dinning)
		{
			*philo->dinning = 1;
			print_msg(philo, " died\n", philo->lock_print);
		}
		usleep(5);
	}
}

int		eval_meal(t_philo *philo)
{
	if (philo->nb_eat < philo->nb_mandatory_eats || philo->nb_mandatory_eats == -2)
		return (1);
	*philo->dinning = 1;
	return (0);
}

void	launch_dinner(t_dinner *dinner)
{
	int	i;

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
	usleep(450);
	while (i < dinner->nb_philos)
	{
		dinner->philos[i]->birth = dinner->start;
		dinner->philos[i]->last_eat = dinner->start;
		pthread_create(&dinner->philos[i]->thread, NULL, live, dinner->philos[i]);
		i += 2;
	}
	while (!dinner->dinning)
		observer(dinner);
	i = -1;
	while (++i < dinner->nb_philos)
		pthread_join(dinner->philos[i]->thread, NULL);
}
