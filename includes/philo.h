/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/04 15:32:39 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/09/27 20:15:56 by parisasadeq   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <time.h>
# include <sys/time.h>
# include <limits.h>
# include <stdint.h>
# include <stdbool.h>

typedef struct s_philo
{
	int				philo_index;
	int				eating_times;
	uint64_t		last_time_eat;
	int				left_fork;
	int				right_fork;
	bool			died;
	pthread_mutex_t	lock;
	pthread_mutex_t	time_lock;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	int				philo_count;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	int				count_must_eat;
	uint64_t		time_to_sleep;
	bool			dead_philo;
	uint64_t		start_time;
	pthread_t		*philos;
	pthread_t		health_check;
	pthread_mutex_t	*forks;
	pthread_mutex_t	fork_lock;
	t_philo			*philo_struct;
	pthread_mutex_t	write;
	pthread_mutex_t	death;
	pthread_mutex_t	start;
}					t_data;

// main
int			main(int argc, char **argv);

// data
t_data		*put_data(char **argv, t_data *data);
t_data		*allocate_memory_data(t_data *data);
int			input_check(int argc, char **argv);
void		free_data(t_data *data);
void		destroy_mutexes(t_data *data, int index);

//prepare philos
int			make_philo(int index, t_data *data);
void		join_philos(pthread_t *philo, t_data *data);
int			make_table(t_data *data);
void		single_philo(t_philo *philo);

//prepare forks
int			make_forks(t_data *data);
void		unlock_forks(t_philo *philo);
int			first_fork_lock(t_philo *philo);
void		second_fork_lock(t_philo *philo);

//checker
void		*health_checker(void	*data_temp);
int			eating_times_check(t_data *data, int i);
int			check_death(t_data *data);
void		death_announcement(t_data *data, int i);
void		*health_checker(void *data_temp);
int			supervisor(t_data *data, int i);

//routine
void		*routine(void *philo);
int			eating_data(t_philo *philo);
void		assign_fork_index(t_philo *philo);
int			take_forks(t_philo *philo);
int			philo_sleeping(t_philo *philo);

// utils
int			ft_atoi(const char *str);
uint64_t	get_time_ms(void);
void		accurate_usleep(uint64_t time, t_philo *philo);
void		print_action(int index, char *action, t_data *data);
int			ft_isdigit(int c);

#endif