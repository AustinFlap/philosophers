/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 18:41:37 by avieira           #+#    #+#             */
/*   Updated: 2021/10/06 18:57:27 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int		invalid_input(int	n, char **args)
{
	int	i;
	int	j;

	if (n == 3 || n == 4)
	{
		i = 0;
		while (++i < n)
		{
			j = -1;
			while (args[i][++j])
				if (args[i][j] < '0' || args[i][j] > '9')
					return (1);
		}
		return (0);
	}
	return (1);
}

int		main(int ac, char **av)
{
	if(invalid_input(ac - 1, av))
		printf("Invalid\n");
	else
		printf("Valid\n");
}
