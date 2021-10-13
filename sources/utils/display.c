/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 04:14:00 by avieira           #+#    #+#             */
/*   Updated: 2021/10/13 04:15:50 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	print_msg(t_philo *philo, char *state, pthread_mutex_t *lock)
{
	struct timeval present;

	if (lock)
		pthread_mutex_lock(lock);
	settimeofday(&present, NULL);
	ft_putnbr_fd(present.tv_sec / (uint64_t)1000, 0);
	write(0, "        ", 8);
	ft_putnbr_fd(philo->id, 0);
	write(0, state, ft_strlen(state));
	if (lock)
		pthread_mutex_unlock(lock);
}
