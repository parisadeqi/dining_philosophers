/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 15:28:53 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/09/27 20:11:13 by parisasadeq   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating_data(t_philo *philo)
{
	uint64_t	time_now;

	if (check_death(philo->data) != 0)
		return (1);
	pthread_mutex_lock(&philo->time_lock);
	time_now = get_time_ms() - philo->data->start_time;
	philo->last_time_eat = time_now;
	philo->eating_times += 1;
	pthread_mutex_unlock(&philo->time_lock);
	if (check_death(philo->data) != 0)
		return (1);
	if (philo->data->count_must_eat != 0)
	{
		if (philo->eating_times > philo->data->count_must_eat)
		{
			return (1);
		}
	}
	return (0);
}

void	assign_fork_index(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	philo->right_fork = philo->philo_index;
	if (philo->philo_index == philo->data->philo_count - 1)
		philo->left_fork = 0;
	else
		philo->left_fork = philo->philo_index + 1;
	pthread_mutex_unlock(&philo->lock);
}

int	take_forks(t_philo *philo)
{
	if (check_death(philo->data) != 0)
		return (1);
	else
	{
		assign_fork_index(philo);
		if (first_fork_lock(philo) != 0)
			return (1);
		if (philo->right_fork != philo->left_fork)
		{
			second_fork_lock(philo);
			if (eating_data(philo) != 0)
			{
				unlock_forks(philo);
				return (1);
			}
			print_action(philo->philo_index + 1, "is eating", philo->data);
			accurate_usleep(philo->data->time_to_eat * 1000, philo);
			unlock_forks(philo);
		}
		else
			return (single_philo(philo), 1);
	}
	return (0);
}

int	philo_sleeping(t_philo *philo)
{
	if (check_death(philo->data) != 0)
		return (1);
	print_action(philo->philo_index + 1, "is sleeping", philo->data);
	accurate_usleep(philo->data->time_to_sleep * 1000, philo);
	if (check_death(philo->data) != 0)
		return (1);
	print_action(philo->philo_index + 1, "is thinking", philo->data);
	return (0);
}

void	*routine(void *philo)
{
	t_philo	*new;

	new = (t_philo *)philo;
	pthread_mutex_lock(&new->data->start);
	pthread_mutex_unlock(&new->data->start);
	if (check_death(new->data) != 0)
		return ((void *)0);
	if (new->data->philo_count > 1 && (new->philo_index + 1) % 2 != 0)
		accurate_usleep(new->data->time_to_eat * 1000, new);
	while (check_death(new->data) == 0)
	{
		if (check_death(new->data) != 0)
			return ((void *)0);
		if (take_forks(philo) != 0)
			return ((void *)0);
		if (check_death(new->data) != 0)
			return ((void *)0);
		if (philo_sleeping(philo) != 0)
			return ((void *)0);
	}
	return ((void *)0);
}
