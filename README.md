# philosophers

Goal of this project was to get familiar with threads and mutexes.

The program is given a philosopher count, time for death, time for sleep and time for eat. Optionally also a number of times a philosopher must eat.

The threads needed to be managed so that one philosopher is one thread and each philosophers brings one fork but two is needed for eating.

If philosophers is unable to eat and time for death comes the program ends. Or if each philosophers has eaten set amount of times.

--- 

**How to use**

In philosophers folder write "make" and run ./philosophers [count] [time_to_die] [time_to_eat] [time_to_sleep] [optionally_times_to_eat]

Time should be written in milliseconds.

---
