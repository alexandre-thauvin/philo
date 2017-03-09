/*
 *
 */

#ifndef PHILO_H_
# define PHILO_H_

#include <pthread.h>
#include <stdbool.h>

enum STATE {REST,
            EAT,
            THINK};

typedef struct		s_philo
{
  pthread_t		    thread;
  pthread_mutex_t	mutex;
  bool			    chopstick;
  struct s_philo	*right;
  enum STATE		state;
  int			    count;
  int			    id;
  int			    *end;
}			        t_philo;

void eat(t_philo *);
void rest(t_philo *);
void think(t_philo *);

#endif /* !PHILO_H_ */
