#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <errno.h>
# define MSG_DIED 0
# define MSG_EATING 1
# define MSG_SLEEPING 2
# define MSG_THINKING 3
# define MSG_FORK 4
# define MSG_LIMIT 5

typedef pthread_mutex_t t_mutex;

typedef struct s_global
{
	int		amount;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		eat_amount;
	int		started_time;
	t_mutex dead;
	t_mutex	print;
	t_mutex	*forks;
}			t_global;

typedef struct s_philo
{
	t_global	*global;
	t_mutex		eat;
	t_mutex		life;
	int			is_eating;
	int			index;
	int			left_fork;
	int			right_fork;
	int			eat_amount;
	int			last_meal;
	int			dead_time;
}				t_philo;

typedef struct	s_all
{
	t_global	*global;
	t_philo		*philos;
}				t_all;

t_philo		*init_philos(t_global *global);
t_global	*init_global(int argc, char *argv[]);
t_mutex		*init_forks(t_global *global);

void		philo_one_eat(t_philo *philo);
void		philo_one_put_forks(t_philo *philo);
void		philo_one_take_forks(t_philo *philo);

void		*philo_one_routine(void *arg);
int			philo_one_launch(t_all all);
void		*philo_one_observer(void *arg);
void		*philo_one_counter(void *arg);

void		print_log(t_philo *philo, int type);
void		*print_error(char *str);
int			ft_atoi(char *str);
int			ft_isspace(int c);
int 		get_time(void);
#endif