# 42-Philosophers
42-Philosophers project aims to simulates the famous Dining Philosophers Problem.
## Dining Philosophers Problem

The dining philosophers problem is a classic synchronization problem used to illustrate the challenges of concurrent programming. It involves philosophers sitting at a round table, where each must alternately think and eat. Eating requires two forks, but there are only as many forks as philosophers, and each philosopher can only pick up the fork to their immediate left and right. The goal is to devise a strategy that ensures no philosopher starves while avoiding deadlock and contention.

## 42 Philosophers Project Overview

The 42 Philosophers project is part of the 42 Cursus, which aims to deepen students' understanding of multithreading and synchronization. In this project, students implement a solution to the dining philosophers problem using threads, ensuring that the philosophers can eat without causing a deadlock or starvation. This involves using synchronization primitives like mutexes to manage access to shared resources (forks).

## Data Races and Mutexes

### Data Races

A data race occurs when two or more threads access shared data simultaneously, and at least one thread modifies the data without proper synchronization. This can lead to unpredictable and erroneous behavior, making it crucial to manage access to shared resources carefully.

### Mutexes

Mutexes (mutual exclusions) are synchronization primitives used to prevent data races by ensuring that only one thread can access a critical section of code at a time. By locking a mutex before accessing shared resources and unlocking it afterward, we can coordinate threads' actions to maintain data integrity and avoid conflicts.

## Usage

To run the project, follow these steps:

1. **Clone the repository:**
   ```sh
   $ git clone https://github.com/usmanUA/42-philosophers
   $ cd philosophers
   $ make
   $ ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]

## Author
    - [@usmanUA](https://github.com/usmanUA)
