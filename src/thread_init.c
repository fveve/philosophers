/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:50:08 by arafa             #+#    #+#             */
/*   Updated: 2024/06/26 08:46:52 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	convert_time(void);

int		ft_death(t_philo *philo);

int		ft_think(t_philo *philo);

int		check_fork(t_philo *philo);

int		ft_take_fork(t_philo *philo);

int		ft_check(t_param *param);

int		ft_check_everyone(t_param *param);

int		ft_init_fork(t_philo *philo, t_param *param, int nb_philo);

int		init_mutex2(t_philo *philo, t_param *param);

void	*ft_philosopher(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->id % 2 == 0)
		usleep(5000);
	while (!ft_check(philo->param) && !ft_check(philo->param))
	{
		check_fork(philo);
	}
	return (NULL);
}

int	init_mutex(t_philo *philo, t_param *param, char *argv1)
{
	int	i;

	i = -1;
	param->nb = ft_atoi(argv1);
	param->fork = malloc(sizeof(pthread_mutex_t) * (param->nb));
	param->is_taken = malloc(sizeof(int) * (param->nb));
	while (++i < param->nb)
		param->is_taken[i] = 0;
	param->is_someone_dead = 0;
	param->index = 0;
	if (!param->fork)
		return (exit_manager("Error, fork mutex was not generated\n",
				philo), 1);
	if (pthread_mutex_init(&param->death, NULL) == -1)
		return (exit_manager("Error, death mutex was not generated",
				philo), 1);
	if (pthread_mutex_init(&param->start_mutex, NULL) == -1)
		return (exit_manager("Error, start_mutex was not generated",
				philo), 1);
	init_mutex2(philo, param);
	ft_init_fork(philo, param, param->nb);
	param->is_taken = memset(param->is_taken, 0, param->nb);
	param->start = convert_time();
	param->everyone_has_eaten = 0;
	return (0);
}

void	init_thread(t_philo *philo, t_param *param)
{
	int	nb;
	int	i;

	i = -1;
	nb = param->nb;
	while (++i < nb)
	{
		philo[i].right_fork = &param->fork[(i + 1) % param->nb];
		if (pthread_create(&philo[i].thread, NULL,
				&ft_philosopher, &philo[i]) == -1)
			exit_manager("Error, thread can't be created\n", philo);
	}
}

t_philo	*init_philo(t_philo *philo, t_param *param, char **argv, int argc)
{
	int	i;

	i = -1;
	philo = malloc(sizeof(t_philo) * (ft_atoi(argv[1])));
	if (!philo)
		return (exit_manager("Error, philo can't be generated\n",
				philo), philo);
	init_mutex(philo, param, argv[1]);
	while (++i < param->nb)
	{
		philo[i].id = i;
		philo[i].dying_time = ft_atoi(argv[2]);
		philo[i].eat_time = ft_atoi(argv[3]);
		philo[i].sleep_time = ft_atoi(argv[4]);
		if (argc == 6)
			philo[i].nb_of_dining = ft_atoi(argv[5]);
		else
			philo[i].nb_of_dining = -1;
		philo[i].left_fork = &param->fork[i];
		philo[i].right_fork = 0;
		philo[i].param = param;
		philo[i].has_eaten = 0;
		philo[i].time_end = convert_time();
	}
	return (philo);
}

void	end_thread(t_philo *philo, t_param *param)
{
	int	nb;
	int	i;

	i = -1;
	nb = param->nb;
	while (++i < nb)
		pthread_join(philo[i].thread, (void *)&philo[i]);
	if (philo->param->everyone_has_eaten == nb)
		printf("All philosophers have eaten\n");
	pthread_mutex_destroy(&param->death);
	i = -1;
	while (++i < param->nb)
		pthread_mutex_destroy(&param->fork[i]);
	pthread_mutex_destroy(&param->start_mutex);
	pthread_mutex_destroy(&param->check_if_dying);
	pthread_mutex_destroy(&param->print_mutex);
	pthread_mutex_destroy(&param->check_everyone);
	free_all(philo, param);
}
