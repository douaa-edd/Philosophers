# Philosophers

**Philosophers** is a project from the **42 School** curriculum. It is an implementation in C of the classic Dining Philosophers problem, originally formulated by Edsger Dijkstra. The objective is to learn the basics of concurrent programming, thread management, and resource synchronization using mutexes.

---

## Overview

One or more philosophers sit at a round table with a large bowl of spaghetti in the middle. There are as many forks on the table as there are philosophers.

Each philosopher continuously alternates between three states:
1. **Eating**: A philosopher needs two forks (one on their left and one on their right) to eat.
2. **Sleeping**: Once done eating, they release both forks and go to sleep.
3. **Thinking**: After waking up, they start thinking until forks become available again.

The simulation stops when:
- A philosopher dies of starvation (the time since their last meal or the start of the simulation exceeds `time_to_die`).
- The optional argument `number_of_times_each_philosopher_must_eat` is provided and all philosophers have eaten at least that many times.

---

## Core Concepts

- **Multithreading** with POSIX threads (`<pthread.h>`).
- **Mutual exclusion & synchronization** using mutexes to protect shared resources (forks, death state, meal counts, print output).
- **Data race prevention** and deadlock avoidance.
- **Accurate time tracking** (`gettimeofday`, `usleep`).

---

## Compilation

Compile the project using `make` (compiled with flags `-Wall -Wextra -Werror -pthread`):

```bash
make
```

Available Makefile rules:
- `make` : Builds the `philo` executable.
- `make clean` : Removes object files (`.o`).
- `make fclean` : Removes object files and the `philo` binary.
- `make re` : Cleans and recompiles the entire project.

---

## Usage

Run the program with the following command syntax:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Arguments

| Argument | Description |
| :--- | :--- |
| `number_of_philosophers` | Number of philosophers and forks around the table. |
| `time_to_die` (in ms) | Maximum time a philosopher can survive without eating before dying. |
| `time_to_eat` (in ms) | Time taken by a philosopher to eat (requires holding two forks). |
| `time_to_sleep` (in ms) | Time a philosopher spends sleeping after eating. |
| `[number_of_times_each_philosopher_must_eat]` *(optional)* | If specified, the simulation stops once every philosopher has eaten at least this many times. |

> All arguments must be integers greater than 0.

---

## Log Format

Each action taken by a philosopher is printed with the following format:

```text
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died
```

- `timestamp_in_ms` is the current timestamp in milliseconds relative to the start of the simulation.
- `X` is the philosopher ID (from 1 to N).
- Status messages do not interleave or scramble thanks to a dedicated display mutex.
- The death message is printed within milliseconds of the philosopher's demise and terminates the simulation.

---

## Examples

- Simulation where no philosopher should die:
```bash
./philo 5 800 200 200
```

- Simulation stopping after every philosopher eats at least 7 times:
```bash
./philo 5 800 200 200 7
```

- Single philosopher test (only 1 fork available, philosopher must die):
```bash
./philo 1 800 200 200
```

- Starvation scenario (a philosopher should not survive):
```bash
./philo 4 310 200 100
```
