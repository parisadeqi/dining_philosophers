/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prepare_philos.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/04 15:32:39 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/09/27 20:15:25 by parisasadeq   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*allocate_memory_data(t_data *data)
{
	data->philo_struct = malloc(sizeof(t_philo) * data->philo_count);
	if (!data->philo_struct)
		return (free(data), NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * (data->philo_count));
	if (!data->forks)
		return (free(data->philo_struct), free(data), NULL);
	data->philos = malloc(sizeof(pthread_t) * (data->philo_count));
	if (!data->philos)
		return (free(data->philo_struct), free(data->forks), free(data), NULL);
	return (data);
}

t_data	*mutex_init(t_data *data)
{
	if (pthread_mutex_init(&data->write, NULL) != 0)
		return (free_data(data), NULL);
	if (pthread_mutex_init(&data->death, NULL) != 0)
	{
		pthread_mutex_destroy(&data->write);
		return (free_data(data), NULL);
	}
	if (pthread_mutex_init(&data->start, NULL))
	{
		pthread_mutex_destroy(&data->write);
		pthread_mutex_destroy(&data->death);
		return (free_data(data), NULL);
	}
	if (make_forks(data) != 0)
	{
		pthread_mutex_destroy(&data->start);
		pthread_mutex_destroy(&data->write);
		pthread_mutex_destroy(&data->death);
		return (free_data(data), NULL);
	}
	return (data);
}

t_data	*put_data(char **argv, t_data *data)
{
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->count_must_eat = 0;
	data->dead_philo = false;
	data->philo_count = ft_atoi(argv[1]);
	if (data->philo_count == 0)
	{
		printf("Really? zero philo?!\n");
		return (free(data), NULL);
	}
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->start_time = get_time_ms();
	data->count_must_eat = 0;
	if (argv[5])
		data->count_must_eat = ft_atoi(argv[5]);
	data = allocate_memory_data(data);
	if (!data)
		return (NULL);
	data = mutex_init(data);
	if (!data)
		return (NULL);
	return (data);
}

int	input_check(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		printf("Please put the right amout of arguments:D\n");
		return (-1);
	}
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (ft_isdigit(argv[i][j]) != 0)
			{
				printf("Please only put digits for arguments:D\n");
				return (-1);
			}
			else
				j++;
		}
		i++;
	}
	return (0);
}
