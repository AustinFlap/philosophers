/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 18:28:20 by avieira           #+#    #+#             */
/*   Updated: 2021/10/06 19:19:01 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define MAX_INT 2147483647

typedef struct	s_input
{
	int			nb_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			nb_mandatory_eats;

}				t_input;

int				ft_atoi_of_pos(const char *nptr);

#endif
