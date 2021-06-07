#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <errno.h>
# define MSG_FORK 1
# define MSG_EAT 2
# define MSG_SLEEP 3
# define MSG_THINK 4
# define MSG_DEAD 5
# define MSG_LIMIT 6
# define SEM_FORKS "S_FORKS"
# define SEM_STOP "S_STOP"
# define SEM_PRINT "S_PRINT"

typedef struct s_params
{
	int		amount;
	int		t_sleep;
	int		t_eat;
	int		t_die;
	int		t_started;
	int		eat_limit;
	int		fed_amount;
	int		last_msg;
	sem_t	*s_stop;
	sem_t	*s_print;	
	sem_t	*s_forks;
}			t_params;

typedef struct s_philo
{
	int			index;
	int			last_eat;
	int			t_wdead;
	int			eat_amount;
	char		*s_eat_name;
	sem_t		*s_eat;
	t_params	*params;
}			t_philo;	

int		init_all(t_philo **tmp, int argc, char *argv[]);
sem_t	*sem_create(char *name, int value);

void	*routine_philo(void *arg);

void	lifespan_take_forks(t_philo *philo);
void	lifespan_put_forks(t_philo *philo);
void	lifespan_eat(t_philo *philo);

void	ft_usleep(int usec);
void	print_log(t_philo *philo, int type);
int		print_error(char *str);
int		ft_atoi(char *str);
int		get_time(void);

void	ft_putnbr(int n);
int		ft_putstr(char *str);
int		ft_putchar(char c);
int		ft_strlen(char *str);

char	*ft_itoa(int nb);
char	*ft_strcpy(char *dst, char *src);
void	*ft_memcpy(void *dst, void *src, int n);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_calloc(int size);
#endif
