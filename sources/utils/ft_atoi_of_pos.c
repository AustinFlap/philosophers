/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 19:09:33 by avieira           #+#    #+#             */
/*   Updated: 2021/10/06 19:18:52 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int					ft_atoi_of_pos(const char *nptr)
{
	const char		*temp;
	long int		nb;
	int				u;

	temp = nptr;
	u = 1;
	nb = 0;

	while (*temp)
		temp++;
	while (temp != nptr)
	{
		temp--;
		if (*temp >= '0' && *temp <= '9')
		{
			nb += (*temp - 48) * u;
			u *= 10;
		}
	}
	if (nb > MAX_INT)
		return (-1);
	return ((int)nb);
}
