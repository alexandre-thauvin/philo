/*
** main.c for  in /home/thauvi_a/rendu/tek2/PSU_2016_philo
**
** Made by Alexandre Thauvin
** Login   <thauvi_a@epitech.net>
**
** Started on  Mon Mar  6 10:55:43 2017 Alexandre Thauvin
** Last update Fri Mar 17 18:29:24 2017 Paul THEIS
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>

#include "philo.h"

static void		p_eat(t_philo *philo)
{

  if (pthread_mutex_trylock(&philo->chopstick) != EBUSY)
    {
      if (pthread_mutex_trylock(&philo->right->chopstick) != EBUSY)
	{
	  write(1, "ed\n", 3);
	  lphilo_take_chopstick(&philo->chopstick);
	  lphilo_take_chopstick(&philo->right->chopstick);
	  lphilo_eat();
	  lphilo_release_chopstick(&philo->chopstick);
	  lphilo_release_chopstick(&philo->right->chopstick);
	  pthread_mutex_trylock(&philo->chopstick);
	  pthread_mutex_unlock(&philo->right->chopstick);
	  philo->state = EAT;
	  --philo->count;
	  write(1, "ee\n", 3);
	}
      pthread_mutex_trylock(&philo->chopstick);
      pthread_mutex_unlock(&philo->chopstick);
    }
}

static void		p_think(t_philo *philo)
{
  if (pthread_mutex_trylock(&philo->chopstick) != EBUSY)
    {
      write(1, "td\n", 3);
      lphilo_take_chopstick(&philo->chopstick);
      lphilo_think();
      lphilo_release_chopstick(&philo->chopstick);
      pthread_mutex_trylock(&philo->chopstick);
      pthread_mutex_unlock(&philo->chopstick);
      philo->state = THINK;
      write(1, "te\n", 3);
    }
  else if (pthread_mutex_trylock(&philo->right->chopstick) != EBUSY)
    {
      write(1, "td\n", 3);
      lphilo_take_chopstick(&philo->right->chopstick);
      lphilo_think();
      lphilo_release_chopstick(&philo->right->chopstick);
      pthread_mutex_trylock(&philo->right->chopstick);
      pthread_mutex_unlock(&philo->right->chopstick);
      philo->state = THINK;
      write(1, "te\n", 3);
    }
}

static void			*choice(void *phil)
{
  t_philo			*philo;

  philo = (t_philo *)phil;
  pthread_barrier_wait(&(*philo->barrier));
  while (*philo->flg && philo->count > 0x00)
    {
      write(1, "-\n", 2);
      p_eat(philo);
      usleep(0x0A);
      if (philo->state == EAT)
	{
	  write(1, "s\n", 2);
	  lphilo_sleep();
	  philo->state = SLEEP;
	}
      if (philo->state != THINK) {
	p_think(philo);
      write(1, "t\n", 2);}
    }
  *philo->flg = 0x00;
  pthread_exit(philo);
}

static bool			philo(int nbPhilo, int nbEat)
{
  int				i;
  bool				flg;
  void				*status;
  t_philo			philos[nbPhilo];
  pthread_barrier_t		barrier;

  i = -0x01;
  flg = true;
  pthread_barrier_init(&barrier, NULL, nbPhilo);
  while (++i < nbPhilo)
    {
      pthread_mutex_init(&philos[i].chopstick, NULL);
      philos[i].state = SLEEP;
      philos[i].count = nbEat;
      philos[i].flg = &flg;
      philos[i].barrier = &barrier;
      philos[i].right = (i == nbPhilo - 0x01) ? (&philos[0]) : (&philos[i + 1]);
      if (pthread_create(&philos[i].thread, NULL, choice, &philos[i]))
        return (fprintf(stderr, "Error - pthread_create()\n"), false);
  }
  while (--i > 0x00)
    if (pthread_join(philos[i].thread, &status))
      return (fprintf(stderr, "Error - pthread_join()\n"), false);
  return (true);
}

int				main(int ac, char **av)
{
  //int				c;
  int				nbPhilo;
  int				nbChopstick;
  //extern char			*optarg;

  RCFStartup(ac, av);
  nbPhilo = 3;
  nbChopstick = 100;
  /*
  while ((c = getopt(ac, av, "p:e:")) != -1)
>>>>>>> bdd33acfaa899452f7c2602bcbe065f1d74d1f9b
    {
    if (c == 'p')
      nbPhilo = atoi(optarg);
    else if (c == 'e')
      nbChopstick = atoi(optarg);
    else
<<<<<<< HEAD
      return (fprintf(stderr, "Usage : philo -p N -e N\n"), 0x01);
    }
  if (nbChopstick <= 0x00 && nbPhilo <= 0x00)
    return (fprintf(stderr, "Usage : philo -p N -e N\n"), 0x01);
=======
      return (fprintf(stderr, "Usage : philo -p N -e N\n"), 1);
    }*/
  if (nbChopstick <= 0 && nbPhilo <= 0)
    return (fprintf(stderr, "Usage : philo -p N -e N\n"), 1);
  philo(nbPhilo, nbChopstick);
  RCFCleanup();
  return (0x00);
}
