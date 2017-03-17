/*
** main.c for  in /home/thauvi_a/rendu/tek2/PSU_2016_philo
**
** Made by Alexandre Thauvin
** Login   <thauvi_a@epitech.net>
**
** Started on  Mon Mar  6 10:55:43 2017 Alexandre Thauvin
** Last update Fri Mar 17 15:39:59 2017 Alexandre Thauvin
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "philo.h"

static void		p_eat(t_philo *philo)
{

  if (printf("%d - ", pthread_mutex_trylock(&philo->chopstick)) &&
      pthread_mutex_trylock(&philo->right->chopstick))
    {
      printf("debut eat ");

      usleep(100);
      lphilo_take_chopstick(&philo->chopstick);
      lphilo_take_chopstick(&philo->right->chopstick);
      lphilo_eat();
      philo->state = EAT;

      lphilo_release_chopstick(&philo->chopstick);
      lphilo_release_chopstick(&philo->right->chopstick);
      //write(1, "before lock\n", 12);
      printf("%d\n", philo->count);
      usleep(100);


      pthread_mutex_unlock(&philo->right->chopstick);


      //write(1, "between lock\n", 13);
      pthread_mutex_unlock(&philo->chopstick);
      printf("fin eat\n");

      //write(1, "afterr lock\n", 12);

      --philo->count;
    }
}

static void		p_think(t_philo *philo)
{
  if (pthread_mutex_trylock(&philo->chopstick) && philo->right->state != THINK)
    {
      //printf("debut think ");

      usleep(100);
      lphilo_take_chopstick(&philo->chopstick);
      lphilo_think();
      lphilo_release_chopstick(&philo->chopstick);
      pthread_mutex_unlock(&philo->chopstick);
      philo->state = THINK;
    }
  else if (pthread_mutex_trylock(&philo->right->chopstick))
    {

      lphilo_take_chopstick(&philo->right->chopstick);
      lphilo_think();
      lphilo_release_chopstick(&philo->right->chopstick);
      pthread_mutex_unlock(&philo->right->chopstick);
      philo->state = THINK;
    }
    usleep(100);

    //printf("fin think\n");

}

static void			*choice(void *phil)
{
  t_philo			*philo;

  philo = (t_philo *)phil;
  pthread_barrier_wait(&(*philo->barrier));
  while (*philo->flg && philo->count > 0x00)
    {
      usleep(100);
      p_eat(philo);
      usleep(0x0A);
      if (philo->state == EAT)
	     {
	       usleep(20);
	        lphilo_sleep();
	         philo->state = SLEEP;
	     }
      usleep(30);
      if (philo->state != THINK)
        p_think(philo);
    }
  *philo->flg = 0;
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
      philos[i].right = (i == nbPhilo - 1) ? (&philos[0]) : (&philos[i + 1]);
      if (pthread_create(&philos[i].thread, NULL, choice, &philos[i]))
        return (fprintf(stderr, "Error - pthread_create()\n"), false);
  }
  while (--i > 0)
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
  nbChopstick = 50;
  /*
  while ((c = getopt(ac, av, "p:e:")) != -1)
    {
    if (c == 'p')
      nbPhilo = atoi(optarg);
    else if (c == 'e')
      nbChopstick = atoi(optarg);
    else
      return (fprintf(stderr, "Usage : philo -p N -e N\n"), 1);
    }*/
  if (nbChopstick <= 0 && nbPhilo <= 0)
    return (fprintf(stderr, "Usage : philo -p N -e N\n"), 1);
  philo(nbPhilo, nbChopstick);
  RCFCleanup();
  return (0);
}
