# **Philosophers**

### **Description**  
Philosophers is a basic implementation of threads in a program. The concept is simple: N philosophers are sitting at a table, each with one fork. They need two forks to eat, so one fork is passed from hand to hand. A philosopher can only wait a certain amount of time, before dying of hunger. Optionally, if all philosophers have eaten a certain amount of times, the program stops.

---

### **Installation And How To Run**  

1. Clone the repository:
   ```bash
   git clone https://github.com/fveve/Philosophers.git
   cd philosophers

2. Compile the project:
   ```bash
   make

3. How to run the project:
   ```bash
   ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
