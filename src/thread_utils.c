/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 08:27:13 by arafa             #+#    #+#             */
/*   Updated: 2024/06/26 08:51:34 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check(t_param *param);

int	ft_death(t_philo *philo);

void	ft_print(t_param *param, char *msg, int id)
{
	pthread_mutex_lock(&param->print_mutex);
	printf("{philosopher[%d] %s", id, msg);
	pthread_mutex_unlock(&param->print_mutex);
}

long	convert_time(void)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	return ((start.tv_usec / 1000) + (start.tv_sec * 1000));
}

void	ft_sleep(t_philo *philo, char *msg, long sleeping_time)
{
	long	time;

	time = convert_time();
	ft_print(philo->param, msg, philo->id + 1);
	while ((convert_time() - time) < sleeping_time
		&& !ft_death(philo) && !ft_check(philo->param))
		usleep(15);
}

int	ft_init_fork(t_philo *philo, t_param *param, int nb_philo)
{
	int	i;

	i = -1;
	while (++i < nb_philo)
	{
		if (pthread_mutex_init(&param->fork[i], NULL) == -1)
			return (exit_manager("Error, fork mutex was not generated\n",
					philo), 1);
	}
	return (0);
}

int	init_mutex2(t_philo *philo, t_param *param)
{
	if (pthread_mutex_init(&param->check_if_dying, NULL) == -1)
		return (exit_manager("Error, check_if_dying mutex was not generated",
				philo), 1);
	if (pthread_mutex_init(&param->print_mutex, NULL) == -1)
		return (exit_manager("Error, print_mutex was not generated",
				philo), 1);
	if (pthread_mutex_init(&param->check_everyone, NULL) == -1)
		return (exit_manager("Error, check_everyone mutex was not generated",
				philo), 1);
	return (0);
}
