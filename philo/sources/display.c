/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 04:14:00 by avieira           #+#    #+#             */
/*   Updated: 2021/10/26 03:36:07 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static void	ft_putc_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(unsigned int n, int fd)
{
	unsigned long int	nb;

	nb = n;
	if (nb < 0)
	{
		ft_putc_fd('-', fd);
		nb *= -1;
	}
	if (nb > 9)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putnbr_fd(nb % 10, fd);
	}
	else
		ft_putc_fd(nb + '0', fd);
}

void	print_msg(t_philo *philo, char *state, pthread_mutex_t *lock)
{
	if (lock)
		pthread_mutex_lock(lock);
	if (!get_dinning(philo))
		printf("%d %d%s", ms_since(&philo->birth, philo->lock_time),
			philo->id, state);
	if (lock)
		pthread_mutex_unlock(lock);
}
