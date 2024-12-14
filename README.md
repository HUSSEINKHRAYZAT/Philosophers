
The "Philosopher Dining Table" problem is a classic synchronization problem in computer science. It illustrates the challenges of avoiding deadlock and ensuring proper resource allocation in concurrent programming.

This project implements a solution to the Philosopher Dining Table problem using C language. The program simulates a dining table with a number of philosophers who alternate between thinking and eating. Philosophers share a limited number of resources forks, and proper synchronization is necessary to ensure that:
No two philosophers eat with the same fork at the same time.
Deadlock does not occur.
Starvation (a philosopher waiting indefinitely) is avoided
