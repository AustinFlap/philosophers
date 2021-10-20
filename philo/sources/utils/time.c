/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 20:05:56 by avieira           #+#    #+#             */
/*   Updated: 2021/10/20 22:23:52 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	usleep_ms(int ms, t_philo *philo)
{
	int sleep_count;

	(void)philo;
	sleep_count = 0;
	usleep(ms * 1000);
	/*
	while (sleep_count < ms && !*philo->dinning)
	{
		if (sleep_count + SLICE_SLEEP > ms)
			usleep((ms - sleep_count) * 1000);
		else	
			usleep(SLICE_SLEEP * 1000);
		sleep_count += SLICE_SLEEP;
	}*/
}

unsigned int	ms_since(struct timeval start)
{
	struct timeval delta;
	struct timeval present;

	gettimeofday(&present, NULL);
	delta.tv_sec = present.tv_sec - start.tv_sec;
	delta.tv_usec = present.tv_usec - start.tv_usec;
	return ((delta.tv_sec * 1000) + (delta.tv_usec / 1000));
}
