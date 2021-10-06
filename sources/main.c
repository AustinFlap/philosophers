/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 18:41:37 by avieira           #+#    #+#             */
/*   Updated: 2021/10/06 19:37:56 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int				invalid_input(int	n, char **args)
{
	int			i;
	int			j;

	if (n == 4 || n == 5)
	{
		i = 0;
		while (++i <= n)
		{
			j = -1;
			while (args[i][++j])
				if (args[i][j] < '0' || args[i][j] > '9')
				{
					printf("Bad argument(s)\n");
					return (1);
				}
		}
		return (0);
	}
	printf("Bad argument(s)\n");
	return (1);
}

int				fill_input(char **args, t_input *input)
{
	input->nb_philos = ft_atoi_of_pos(args[1]);
	input->time_to_die = ft_atoi_of_pos(args[2]);
	input->time_to_eat = ft_atoi_of_pos(args[3]);
	input->time_to_sleep = ft_atoi_of_pos(args[4]);
	if (args[5])
		input->nb_mandatory_eats = ft_atoi_of_pos(args[5]);
	else
		input->nb_mandatory_eats = 0;

	
	printf("nb_philos         : %d\n",input->nb_philos);
	printf("time_to_die       : %d\n",input->time_to_die);
	printf("time_to_eat       : %d\n",input->time_to_eat);
	printf("time_to_sleep     : %d\n",input->time_to_sleep);
	printf("nb_mandatory_eats : %d\n",input->nb_mandatory_eats);

	if (input->nb_philos == -1 || input->time_to_die == -1 ||
					input->time_to_eat == -1 || input->time_to_sleep == -1 ||
												input->nb_mandatory_eats == -1)
	{
		printf("Int overflow arguments\n");
		return (1);
	}
	else if (input->nb_philos < 2)
	{
		printf("At least 2 philosophers needed\n");
		return (1);
	}
	return (0);
}

int				main(int ac, char **args)
{
	t_input		input;

	if(invalid_input(ac - 1, args))
		return (0);
	if (fill_input(args, &input))
		return (0);
}
