/*
** main.c for  in /home/thauvi_a/rendu/tek2/PSU_2016_philo
**
** Made by Alexandre Thauvin
** Login   <thauvi_a@epitech.net>
**
** Started on  Mon Mar  6 10:55:43 2017 Alexandre Thauvin
** Last update Fri Mar 10 18:17:52 2017 Paul THEIS
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "philo.h"

static bool			choice(t_philo *philo)
{
  while (*philo->flg && philo->count > 0x00)
    {
      p_eat(philo);
      usleep(10);
      if (philo->state == EAT)
        p_sleep(philo);
      if (philo->state != THINK)
        p_think(philo);
    }
  return (!(*philo->flg = false));
}

static void			*print_philo (void *phil)
{
  t_philo			*philo;

  philo = (t_philo *)phil;
  pthread_barrier_wait(&(*philo->barrier));
  if (choice(philo))
    return (pthread_exit(philo), NULL);
  return (NULL);
}

static bool			philo(int nbPhilo, int nbEat)
{
  int				i;
  bool				flg;
  void				*status;
  t_philo			philos[nbPhilo];
  pthread_barrier_t		barrier;

  i = -1;
  flg = true;
  pthread_barrier_init(&barrier, NULL, nbPhilo);
  while (++i < nbPhilo)
    {
      pthread_mutex_init(&philos[i].mutex, NULL);
      philos[i].state = SLEEP;
      philos[i].count = nbEat;
      philos[i].flg = &flg;
      philos[i].barrier = &barrier;
      philos[i].right = (i == nbPhilo - 1) ? (&philos[0]) : (&philos[i + 1]);
      if (pthread_create(&philos[i].thread, NULL, print_philo, &philos[i]))
        return (fprintf(stderr, "Error - pthread_create()\n"), false);
  }
  while (--i > 0)
    if (pthread_join(philos[i].thread, &status))
      return (fprintf(stderr, "Error - pthread_join()\n"),false);
  return (true);
}

int				main(int ac, char **av)
{
  int				c;
  int				nbPhilo;
  int				nbChopstick;
  extern char			*optarg;

  RCFStartup(ac, av);
  nbPhilo = 0;
  nbChopstick = 0;
  while ((c = getopt(ac, av, "p:e:")) != -1)
    {
    if (c == 'p')
      nbPhilo = atoi(optarg);
    else if (c == 'e')
      nbChopstick = atoi(optarg);
    else
      return (fprintf(stderr, "Usage : philo -p N -e N\n"), 1);
    }
  if (nbChopstick <= 0 && nbPhilo <= 0)
    return (fprintf(stderr, "Usage : philo -p N -e N\n"), 1);
  philo(nbPhilo, nbChopstick);
  RCFCleanup();
  return (0);
}
