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
	uint64_t				last_time_eat;
	int				left_fork;
	int				right_fork;
	bool			died;
	pthread_mutex_t	lock;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	int				philo_count;
	uint64_t				time_to_die;
	uint64_t				time_to_eat;
	int				count_must_eat;
	uint64_t				time_to_sleep;
	bool			dead_philo;
	uint64_t			start_time;
	pthread_t		*philos;
	pthread_t		health_check;
	pthread_mutex_t	*forks;
	pthread_mutex_t	fork_lock;
	t_philo			*philo_struct;
	pthread_mutex_t	write;
	pthread_mutex_t	death;

}					t_data;

int		main(int argc, char **argv);
int		ft_atoi(const char *str);
t_data	*put_data(char **argv, t_data *data);
void	*routine(void *philo);
uint64_t	get_time_ms(void);
void	destroy_mutexes(t_data *data);
void	accurate_usleep(uint64_t time, t_philo *philo);
void	print_action(int index, char *action, t_data *data);
void	make_philo(int index, t_data *data);
void	join_philos(pthread_t *philo, t_data *data);
void	*health_checker(void	*data_temp);
void	make_table(t_data *data);
void	make_forks(t_data *data);
void	unlock_forks(t_philo *philo);
int		eating_times_check(t_data *data, int i);
int		supervisor(t_data *data, int i);
void	*health_checker(void *data_temp);
void	lock_forks(t_philo *philo);
int		check_death(t_data *data);

#endif