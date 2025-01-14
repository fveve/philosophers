/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:51:00 by arafa             #+#    #+#             */
/*   Updated: 2024/06/26 10:10:50 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		ft_think(t_philo *philo);

long	convert_time(void);

int		ft_death(t_philo *philo);

void	ft_print(t_param *param, char *msg, int id);

void	ft_sleep(t_philo *philo, char *msg, long sleeping_time);

int	ft_check(t_param *param)
{
	pthread_mutex_lock(&param->check_if_dying);
	if (param->is_someone_dead)
	{
		pthread_mutex_unlock(&param->check_if_dying);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&param->check_if_dying);
		return (0);
	}
}

int	ft_check_everyone(t_param *param)
{
	pthread_mutex_lock(&param->check_everyone);
	if (param->everyone_has_eaten != param->nb)
	{
		pthread_mutex_unlock(&param->check_everyone);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&param->check_everyone);
		return (1);
	}
}

int	ft_take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (ft_check(philo->param) || philo->has_eaten == philo->nb_of_dining)
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	else
		ft_print(philo->param, "has taken a fork}\n\n", philo->id + 1);
	pthread_mutex_lock(philo->right_fork);
	ft_print(philo->param, "has taken a second fork}\n\n", philo->id + 1);
	philo->time_end = convert_time();
	if (!ft_check(philo->param))
		ft_sleep(philo, "is eating}\n\n", philo->eat_time);
	if (philo->has_eaten != philo->nb_of_dining)
		philo->has_eaten++;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (!ft_check(philo->param))
		ft_sleep(philo, " is sleeping}\n\n", philo->sleep_time);
	return (0);
}

int	ft_death(t_philo *philo)
{
	if (!ft_check(philo->param)
		&& (convert_time() - philo->time_end) >= philo->dying_time
		&& !ft_check_everyone(philo->param)
		&& philo->has_eaten != philo->nb_of_dining)
	{
		pthread_mutex_lock(&philo->param->death);
		philo->param->is_someone_dead = 1;
		ft_print(philo->param, "is dead}\n\n", philo->id);
		pthread_mutex_unlock(&philo->param->death);
		return (1);
	}
	return (0);
}

int	check_fork(t_philo *philo)
{
	if (!ft_check_everyone(philo->param) && !ft_check(philo->param)
		&& philo->has_eaten != philo->nb_of_dining)
	{
		if (ft_check(philo->param) || ft_check_everyone(philo->param)
			|| ft_take_fork(philo))
		{
			pthread_mutex_unlock(&philo->param->death);
			return (1);
		}
		else if (philo->has_eaten == philo->nb_of_dining)
		{
			philo->param->everyone_has_eaten++;
			return (1);
		}
		else if (!ft_check(philo->param))
			ft_print(philo->param, "is thinking}\n\n", philo->id + 1);
	}
	return (1);
}
