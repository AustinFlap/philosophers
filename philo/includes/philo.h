/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 18:28:20 by avieira           #+#    #+#             */
/*   Updated: 2021/10/20 22:22:43 by avieira          ###   ########.fr       */
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
# define SLICE_SLEEP 1

typedef	enum			e_action
{
						eating,
						sleeping,
						thinking,
						dead,
}						t_action;

typedef	struct			s_philo
{
	int					id;
	int					nb_eat;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_mandatory_eats;
	struct timeval		last_eat;
	struct timeval		birth;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*lock;
	pthread_mutex_t		*lock_print;
	int					*dinning;
	t_action			*action;

}						t_philo;


typedef struct			s_dinner
{
	int					nb_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_mandatory_eats;
	int					dinning;
	struct timeval		start;
	pthread_mutex_t		lock;
	pthread_mutex_t		lock_print;
	pthread_mutex_t		*forks;
	t_philo				**philos;

}						t_dinner;

int						ft_atoi_of(const char *nptr);
void					create_dinner(t_dinner *dinner);
void					launch_dinner(t_dinner *dinner);
void					destroy_dinner(t_dinner *dinner);
void					usleep_ms(int ms, t_philo *philo);
void					ft_putnbr_fd(unsigned int n, int fd);
void					print_msg(t_philo *philo, char *state, pthread_mutex_t *lock);
int						ft_strlen(char *str);
unsigned int			ms_since(struct timeval start);
void					*live(void *p_philo);
void					*observer(void *p_philo);

#endif
