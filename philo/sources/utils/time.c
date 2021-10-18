/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 20:05:56 by avieira           #+#    #+#             */
/*   Updated: 2021/10/13 14:16:58 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	usleep_ms(int ms)
{
	usleep(ms * 1000);
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
