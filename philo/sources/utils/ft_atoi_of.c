/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_of.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 20:44:21 by avieira           #+#    #+#             */
/*   Updated: 2021/10/13 12:33:28 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	ft_atoi_of(const char *nptr)
{
	int					i;
	int					neg;
	unsigned long long	n;

	i = 0;
	n = 0;
	neg = 1;
	while ((nptr[i] > 8 && nptr[i] < 14) || nptr[i] == 32)
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
		if (nptr[i++] == '-')
			neg = -1;
	if (i == (int)ft_strlen((char *)nptr))
		return (-1);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		n = 10 * n + (nptr[i++] - '0');
		if ((n > 2147483647 && neg == 1) || (n > 2147483648 && neg == -1))
			return (-1);
	}
	if (i == 0 || i != (int)ft_strlen((char *)nptr))
		return (-1);
	return ((int)n * neg);
}
