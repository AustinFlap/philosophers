/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 04:14:00 by avieira           #+#    #+#             */
/*   Updated: 2021/10/25 23:58:30 by avieira          ###   ########.fr       */
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
	//(void)lock;
	if (lock)
		pthread_mutex_lock(lock);
	if (!get_dinning(philo))
		printf("%d %d%s", ms_since(&philo->birth, philo->lock_time), philo->id, state);
	/*
	ft_putnbr_fd(ms_since(philo->birth), 1);
	write(1, " ", 1);
	ft_putnbr_fd(philo->id, 1);*/
	//write(1, state, ft_strlen(state));
	if (lock)
		pthread_mutex_unlock(lock);
}
