cmake_minimum_required(VERSION 3.6)
project(PSU_2016_philo)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        include/extern.h
        include/philo.h
        src/main.c
        libriceferee.so
        Makefile)

add_executable(PSU_2016_philo ${SOURCE_FILES})