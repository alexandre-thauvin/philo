/*
** main.c for  in /home/thauvi_a/rendu/tek2/PSU_2016_philo
**
** Made by Alexandre Thauvin
** Login   <thauvi_a@epitech.net>
**
** Started on  Mon Mar  6 10:55:43 2017 Alexandre Thauvin
** Last update Tue Mar  7 23:31:11 2017 Paul THEIS
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "philo.h"
#include "extern.h"
#include "../include/philo.h"
#include "../include/extern.h"

pthread_barrier_t mutex_stock;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void choice(t_philo *philo)
{
  //on reçoit direct le philo
  //à remplacer plus tard par un void* name(void *) vu qu'on l'appellera direct lors du pthread_create
//  t_philo *philo;

  //philo = (t_philo *)arg;
  pthread_barrier_wait(&mutex_stock);
  while (philo->count > 0)
    {
      usleep(10);
      eat(philo);
      if (philo->state == EAT)
        rest(philo);
      if (philo->state != THINK)
        think(philo);
    }
}


static void     *print_philo (void *phil)
{
  t_philo	    *philo;
  int		    s;

  philo = (t_philo *)phil;
<<<<<<< HEAD
=======
  choice(phil);
  // Attendre que les nbPhilo soit là avant de continuer.

>>>>>>> da2fdcdcdc5a2883d5ffdf83b8e21f3769e6e59e
  s = pthread_barrier_wait(&mutex_stock);
  pthread_mutex_lock(&mutex);
  if(s == 0) {
    printf("Thread %ld passed barrier %d: return value was 0\n", philo->thread, philo->id);
  } else if (s == PTHREAD_BARRIER_SERIAL_THREAD) {
    printf("Thread %ld passed barrier %d: return value was PTHREAD_BARRIER_SERIAL_THREAD\n", philo->thread, philo->id);
  } else {
    printf("pthread_barrier_wait (%ld)", philo->thread);
    exit(EXIT_FAILURE);
  }
  printf("+-------------------------------+\n");
  printf("| PHILO \t%-16d|\n", philo->id);
  printf("+-------------------------------+\n");
  printf("| Thread: \t%-16ld|\n", philo->thread);
  printf("| end: \t\t%-16p|\n", (void*)philo->end);
  printf("| chopstick: \t%-16s|\n", (philo->chopstick) ? "true" : "false");
  printf("| Right: \t%-16p|\n", (void *)philo->right);
  printf("| State: \t%-16d|\n", philo->state);
  printf("| count: \t%-16d|\n", philo->count);
  printf("| id: \t\t%-16d|\n", philo->id);
  printf("+-------------------------------+\n");
  printf("| addr: \t%-16p|\n", (void *)philo);
  printf("+-------------------------------+\n");
//  lphilo_eat();
//  lphilo_think();
//  lphilo_sleep();
  pthread_mutex_unlock(&mutex);
  pthread_exit(NULL);
  return (NULL);
}

int		    philo(int nbPhilo, int nbEat)
{
  int 		i;
  int  		end;
  t_philo 	philos[nbPhilo];

  i = -1;
  end = 0;
  pthread_barrier_init(&mutex_stock, NULL, nbPhilo);
  while (++i < nbPhilo)
    {
      philos[i].right = (i == nbPhilo - 1) ? (&philos[0]) : (&philos[i + 1]);
      philos[i].state = REST;
      philos[i].count = nbEat;
      philos[i].chopstick = true;
      philos[i].id = i;
      philos[i].end = &end;
      pthread_mutex_init(&philos[i].mutex, NULL); //PTHREAD_MUTEX_INITIALIZER;
      if (pthread_create(&philos[i].thread, NULL, print_philo, &philos[i]))
        return (fprintf(stderr,"Error - pthread_create() return code: %d\n", -1), 1);
  }
  i = 0;
  while (i < nbPhilo)
    if (pthread_join(philos[i++].thread, NULL))
      return (fprintf(stderr, "Error - pthread_join()\n"), 1);
  return (0);
}

int			    main(int ac, char **av)
{
  int           c;
  int			nbPhilo;
  int			nbEat;
  extern char   *optarg;
  extern int    optind;

  optind = 0;
  nbChopstick = 0;
  nbPhilo = 0;
  while ((c = getopt(ac, av, "p:e:")) != -1)
  {
    if (c == 'p')
      nbPhilo = atoi(optarg);
    else if (c == 'e')
<<<<<<< HEAD
      nbChopstick = atoi(optarg);
    else
      return (fprintf(stderr, "Usage : philo -p N -e N\n"), 1);
  }
  if (nbChopstick <= 0 && nbPhilo <= 0)
    return (fprintf(stderr, "Usage : philo -p N -e N\n"), 1);
  RCFStartup(ac, av);
  philo(nbPhilo, nbChopstick);
=======
      nbEat = atoi(optarg);
    else if (c == ':')
      fprintf(stderr, "Option -%c requires an operand: %d\n", optopt, ++errflg);
    else if (c == '?')
        fprintf(stderr, "Unrecognized option: -%c: %d\n", optopt, ++errflg);
  }
  if (errflg) {
    fprintf(stderr, "Usage : philo -p N -e N");
    exit(2);
  }
  printf("%d : %d\n", nbPhilo, nbEat);
  philo(nbPhilo, nbEat);
>>>>>>> da2fdcdcdc5a2883d5ffdf83b8e21f3769e6e59e
  RCFCleanup();
  return (0);
}
