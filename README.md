# philosophers

Project completed on: 125/125

The main goal of this project: acquaintance with multithreading, in the main part, and with multiprocessing, in the bonus part, as well as with mutexes and semaphores.

The main idea: there are n-th number of philosophers who must eat, sleep, think. For eating, everyone needs to have 2 forks, one in the right hand, the other in the left. The number of forks is equal to the number of philosophers (7 philosophers = 7 forks)

The program can take 4 or 5 arguments.
Startup example: ./filo 5 800 200 200 (5)
5 - the total number of philosophers and forks they can use
800 is the time in milliseconds that a philosopher can live without food. If during this period of time he does not have time to eat, then he dies and the whole program will stop.
200 (1) is the time in milliseconds that the philosopher spends on eating.
200 (2) is the time in milliseconds that the philosopher spends on sleep.
5 is an optional argument that specifies how many times each philosopher must eat in order for the program to complete.
