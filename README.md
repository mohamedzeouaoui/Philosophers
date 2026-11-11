<h1 align="center">Philosophers</h1>

<p align="center">
  <em>I never thought philosophy would be so deadly.</em><br>
  The classic dining philosophers problem, solved with threads and mutexes in C.
</p>

<p align="center">
  <img alt="Language" src="https://img.shields.io/badge/language-C-blue">
  <img alt="Norm" src="https://img.shields.io/badge/norminette-passing-brightgreen">
  <img alt="42" src="https://img.shields.io/badge/school-42-black">
</p>

---

## Table of Contents

- [About](#about)
- [The Problem](#the-problem)
- [Installation](#installation)
- [Usage](#usage)
- [Output](#output)
- [Examples](#examples)
- [Project Structure](#project-structure)
- [How It Works](#how-it-works)
- [Testing](#testing)
- [Allowed Functions](#allowed-functions)
- [Author](#author)
- [Acknowledgments](#acknowledgments)

---

## About

**Philosophers** is a 42 project about the basics of **multithreading** and **synchronization**. It simulates the *dining philosophers problem*: several philosophers sit around a table and must share forks to eat, without ever starving and without causing a deadlock or a data race.

Each philosopher is a **thread**, and each fork is protected by a **mutex**.

## The Problem

- One or more philosophers sit at a round table with a big bowl of spaghetti in the middle.
- There are as many forks as philosophers, with one fork between each pair.
- A philosopher needs **two forks** (left and right) to eat.
- Philosophers alternate between **eating**, **sleeping** and **thinking**.
- A philosopher who does not start eating within `time_to_die` milliseconds since the start of their last meal (or the start of the simulation) **dies**.
- The simulation stops when a philosopher dies, or when every philosopher has eaten the required number of times.

## Installation

### Requirements

- A UNIX-like system (Linux or macOS)
- `cc` or `gcc`
- `make`

### Build

```bash
git clone https://github.com/mohamedzeouaoui/Philosophers.git
cd Philosophers/philo
make
```

### Makefile rules

| Rule          | Description                              |
|---------------|------------------------------------------|
| `make`        | Compile the project                      |
| `make clean`  | Remove object files                      |
| `make fclean` | Remove object files and the executable   |
| `make re`     | Recompile from scratch                   |

## Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

| Argument                                         | Description                                                      |
|--------------------------------------------------|------------------------------------------------------------------|
| `number_of_philosophers`                         | Number of philosophers, and also of forks                        |
| `time_to_die` (ms)                               | Time a philosopher can live without starting a meal              |
| `time_to_eat` (ms)                               | Time a philosopher takes to eat (holding two forks)              |
| `time_to_sleep` (ms)                             | Time a philosopher spends sleeping                               |
| `number_of_times_each_philosopher_must_eat`      | Optional. The simulation stops once everyone has eaten this many times |

## Output

Every state change is printed in this format, with no overlapping lines:

```text
<timestamp_in_ms> <philosopher_id> has taken a fork
<timestamp_in_ms> <philosopher_id> is eating
<timestamp_in_ms> <philosopher_id> is sleeping
<timestamp_in_ms> <philosopher_id> is thinking
<timestamp_in_ms> <philosopher_id> died
```

- The timestamp is the number of milliseconds since the start of the simulation.
- A death message is printed within **10 ms** of the actual death.

## Examples

```bash
# 5 philosophers, nobody should die
./philo 5 800 200 200

# Same, but stops after each philosopher has eaten 7 times
./philo 5 800 200 200 7

# One philosopher: only one fork, so he must die
./philo 1 800 200 200

# A philosopher should die
./philo 4 310 200 100
```

## Project Structure

```text
Philosophers/
└── philo/
    ├── Makefile
    ├── philo.h           # Structures and prototypes
    ├── main.c            # Entry point
    └── ...               # Parsing, initialization, routine, monitor, utils
```

> Adjust this tree to match your own files.

## How It Works

1. **Parse**: the arguments are validated (positive integers only, no overflow, a sensible number of philosophers).
2. **Init**: the forks (mutexes), the philosophers and the shared data are created.
3. **Start**: one thread is created per philosopher, and the start time is recorded.
4. **Routine**: each philosopher loops through taking forks, eating, sleeping and thinking.
5. **Avoiding deadlocks**: philosophers do not all grab forks in the same order (for example, even and odd philosophers start with different forks, or a small delay is added at the start), so the circular wait cannot happen.
6. **Monitor**: a check runs continuously to detect a death or the end condition (everyone has eaten enough), and stops the simulation.
7. **Protecting shared data**: the last meal time, the meal counter, the stop flag and the printing are all protected by mutexes, so there are no data races.
8. **Cleanup**: threads are joined, mutexes destroyed and memory freed.

## Testing

Check for data races and deadlocks with the thread sanitizers:

```bash
# Helgrind
valgrind --tool=helgrind ./philo 5 800 200 200 5

# DRD
valgrind --tool=drd ./philo 5 800 200 200 5

# ThreadSanitizer (add -fsanitize=thread to the compile flags)
```

Cases worth testing:

- `1 800 200 200`: the philosopher dies after `800` ms
- `5 800 200 200`: no one dies
- `5 800 200 200 7`: stops when everyone has eaten 7 times
- `4 410 200 200`: no one dies
- `4 310 200 100`: someone dies
- Large numbers of philosophers (`200` and more) and very short times
- Invalid inputs: zero, negative numbers, letters, empty arguments, overflow

## Allowed Functions

`memset`, `printf`, `malloc`, `free`, `write`, `usleep`, `gettimeofday`, `pthread_create`, `pthread_detach`, `pthread_join`, `pthread_mutex_init`, `pthread_mutex_destroy`, `pthread_mutex_lock`, `pthread_mutex_unlock`

## Author

- **Mohamed Zeouaoui**: [@mohamedzeouaoui](https://github.com/mohamedzeouaoui)

## Acknowledgments

- The 42 network for the subject and the peer-learning environment
- Edsger Dijkstra, for the original dining philosophers problem
- The `pthread` man pages
