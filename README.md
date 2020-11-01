# philosophers
21-School (Ecole42) 'philosophers' project.

## Description
The goal of this project is to get basics of threading a process and how to
work on the same memory space. To study how to make threads and discover
the mutex, semaphore and shared memory.

There are 3 programs. All of them has common rules:
* A number of philosophers are sitting at a round table doing one of three things: eating, thinking or sleeping.
* While eating, they are not thinking or sleeping, while sleeping, they are not eating or thinking and of course, while thinking, they are not eating or sleeping.
* The philosophers sit at a circular table with a large bowl of spaghetti in the center.
* There are some forks on the table.
* As spaghetti is difficult to serve and eat with a single fork, it is assumed that a philosopher must eat with two forks, one for each hand.
* The philosophers must never be starving.
* Every philosopher needs to eat.
* Philosophers don’t speak with each other.
* Philosophers don’t know when another philosopher is about to die.
* Each time a philosopher has finished eating, he will drop his forks and start sleeping.
* When a philosopher is done sleeping, he will start thinking.
* The simulation stops when a philosopher dies.
* Each program should have the same options: number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

`number_of_philosophers`: is the number of philosophers and also the number of forks.

`time_to_die`: is in milliseconds, if a philosopher doesn’t start eating ’time_to_die’ milliseconds after starting his last meal or the beginning of the simulation, it dies.

`time_to_eat`: is in milliseconds and is the time it takes for a philosopher to eat. During that time he will need to keep the two forks.

`time_to_sleep`: is in milliseconds and is the time the philosopher will spend sleeping.

`number_of_times_each_philosopher_must_eat`: argument is optional, if all philosophers eat at least number_of_times_each_philosopher_must_eat’ the simulation will stop. If not specified, the simulation will stop only at the death of a philosopher.

... and each of them has non common rules:

### philo_one
* One fork between each philosopher, therefore there will be a fork at the right and
at the left of each philosopher.
* To avoid philosophers duplicating forks, you should protect the forks state with a
mutex for each of them.
* Each philosopher should be a thread.

### philo_two
* All the forks are in the middle of the table.
* They have no states in memory but the number of available forks is represented by a semaphore.
* Each philosopher should be a thread.

### philo_three
* All the forks are in the middle of the table.
* They have no states in memory but the number of available forks is represented by a semaphore.
* Each philosopher should be a process and the main process should not be a philoso-pher.

## Usage
To build program, run:

`make` in directory `philo_one/`, `philo_two/` or `philo_three/`

To launch program, run (examples):
```
./philo_one 5 800 200 200
```
*no one should die*

```
./philo_two 5 800 200 200 7
```
*no one should die and the simulation should stop when all the philosopher has eaten 7 times*

```
./philo_three 4 410 200 200
```
*no one should die*

```
./philo_one 4 310 200 100
```
*a philosopher should die*
