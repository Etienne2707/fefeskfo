
#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>

typedef struct s_philo {
	int					id;
	long int			nb_eat;
	long int			last_eat;
	pthread_t			t_id;
	pthread_mutex_t    *forks_r;
	pthread_mutex_t    forks_l;
	pthread_mutex_t    time_lock;
	pthread_mutex_t    lock_eat;

}               t_philo;

typedef struct s_info {

    int					die;
	int					nb_philo;
	long int			time_start;
	long int			time_die;
	long int			time_eat;
	long int			time_sleep;
	long int			counter_eat;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		eat_lock;

}           t_info;

int main(int argc, char **argv);
int check_arg(int ac, char **argv);
int     init_info(char **argv, char argc, t_info *info, t_philo *philo);
int    init_all(char **argv, int argc, t_philo *philo, t_info *info);
void *routine_philo(void *data);
int    init_thread(t_info *info, t_philo *philo);
int	ft_usleep(long int time);
long int	get_current_time(void);
t_info	*get_info(void);
int	die_checker(t_philo *philo);
int	print(t_philo *philo, char *str);
int die_monitor(t_philo *philo, t_info *info);
int	print(t_philo *philo, char *str);
int destroy_mutex(t_info *info,t_philo *philo);
int	ft_atoi(const char *str);

#endif