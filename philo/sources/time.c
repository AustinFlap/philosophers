/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 20:05:56 by avieira           #+#    #+#             */
/*   Updated: 2021/10/26 17:48:30 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	usleep_ms(int ms, t_philo *philo, struct timeval *start)
{
	struct timeval	tmp;

	if (start == NULL)
	{
		start = &tmp;
		get_time(start, philo->lock_time);
	}
	while (ms_since(start, philo->lock_time) < (unsigned int)ms
		&& !get_dinning(philo))
		usleep(1000);
}

void	get_time(struct timeval *time, pthread_mutex_t *lock)
{
	if (lock)
		pthread_mutex_lock(lock);
	gettimeofday(time, NULL);
	if (lock)
		pthread_mutex_unlock(lock);
}

unsigned int	ms_since(struct timeval *start, pthread_mutex_t *lock)
{
	struct timeval	delta;
	struct timeval	present;

	if (lock)
		pthread_mutex_lock(lock);
	get_time(&present, NULL);
	delta.tv_sec = present.tv_sec - start->tv_sec;
	delta.tv_usec = present.tv_usec - start->tv_usec;
	if (lock)
		pthread_mutex_unlock(lock);
	return ((delta.tv_sec * 1000) + (delta.tv_usec / 1000));
}
