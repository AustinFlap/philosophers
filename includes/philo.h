/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 18:28:20 by avieira           #+#    #+#             */
/*   Updated: 2021/10/13 14:17:04 by avieira          ###   ########.fr       */
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

typedef	enum			e_action
{
						null,
						eat,
						rest,
						think,
						death,
}						t_action;

typedef	struct			s_philo
{
	int					id;
	int					nb_eat;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	struct timeval		*birth;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*lock;

}						t_philo;


typedef struct			s_simulation
{
	int					nb_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_mandatory_eats;
	struct timeval		start;
	pthread_mutex_t		lock;
	pthread_mutex_t		*forks;
	t_philo				**philos;

}						t_simulation;

int						ft_atoi_of(const char *nptr);
void					create_simulation(t_simulation *simulation);
void					launch_simulation(t_simulation *simulation);
void					destroy_simulation(t_simulation *simulation);
void					usleep_ms(int ms);
void					ft_putnbr_fd(unsigned int n, int fd);
void					print_msg(t_philo *philo, char *state, pthread_mutex_t *lock);
int						ft_strlen(char *str);
unsigned int						ms_since(struct timeval start);

#endif
