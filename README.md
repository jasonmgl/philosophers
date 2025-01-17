# PHILOSOPHERS
The "Philosophers' Dinner" problem is a classic synchronization and concurrency issue in computer science. This project simulates the scenario where multiple philosophers sit at a table, each alternating between thinking and eating. To eat, a philosopher requires two forks (or chopsticks) but must share them with their neighbors, leading to potential conflicts and the need for proper resource management. The primary objective is to prevent deadlock and ensure that all philosophers can eat without causing a system halt.

## USAGE
Clone the Repository:

```bash
git clone https://github.com/jasonmgl/philosophers.git
```
Navigate to the Directory:

```bash
cd philosophers
```
Compile the Program:

Use the provided Makefile to compile the project:

```bash
make
```
This will generate the executable philosophers.

Run the Simulation:

Execute the program with the required arguments:

```bash
./philosophers [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
```
- number_of_philosophers: Total number of philosophers and forks.
- time_to_die: Time (in milliseconds) a philosopher can live without eating.
- time_to_eat: Time (in milliseconds) a philosopher spends eating.
- time_to_sleep: Time (in milliseconds) a philosopher spends sleeping.
- number_of_times_each_philosopher_must_eat (optional): Number of times each philosopher needs to eat before the simulation ends.

Example:

```bash
./philosophers 5 800 200 200
```
This command starts a simulation with 5 philosophers, where each has 800ms to live without eating, spends 200ms eating, and 200ms sleeping.

## DEPENDENCIES
- Compiler: Requires a C compiler like gcc.
- Make: Utilizes make for building the project.
- POSIX Threads Library: The simulation relies on POSIX threads (pthreads) for concurrent execution. Ensure that your system supports pthreads.
