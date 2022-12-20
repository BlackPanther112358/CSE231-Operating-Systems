# DINING PHILOSOPHERS

We have to simulate $5$ Philosophers eating and thinking while sitting on a table, using only 5 forks. Each philosopher can only pick forks placed on his either side.

To avoid deadlock, every philosopher always prefers the fork with minimal index available to him. In simpler words, every philosopher is left-handed, but the last philosopher is right-handed. This ensures that at least $1$ one of the available forks will the preferred fork to be picked up first for $2$ philosophers, thus, avoiding the scenario where each philosopher picks $1$ fork, resulting in deadlock.

## PART A

Initially we will use strict resource ordering (using the mutex locks) to simulate the forks. Every philosopher will then use mutex to try to access his foremost preferred fork. Once that is acquired, he will then acquire the other fork similarly. Once both forks are available, he will start to eat.

The philosopher will then eat for random time between 10 and 20 seconds, both included. Once he is done eating, he will put down both forks and start thinking for some time (between 10 and 20 seconds).

This process will run a certain number of times for every philosopher, indicated by the magic number $HUNGER$ in the code, after which the philosopher leaves the table.

For second part, we cannot use resource hierachy. Thus, we will make a helper function, $\small{pick\_forks}$, which will try to acquire both forks. If both are available, it will return $1$, else it will return $0$. This will be called by the philosopher thread, which will then eat if the function returns $1$.

#### <u>IMPLEMENTATION</u>

We use 2 magic numbers, $\small{PHILOSOPHER\_CNT}$ to represent number of philosophers and $\small{HUNGER}$ to represent the number of times a philosopher will eat and think.

We will make 2 structs for $\small{PHILOSOPHER}$ and $\small{FORK}$ and use them to implement the above process. The $\small{PHILOSOPHER}$ struct will have the reference to the $\small{FORK}$ structs on his left and right, and the $\small{FORK}$ struct will have the mutex lock and the semaphore respectively.

We will then generate $2$ arrays, one for the $\small{PHILOSOPHER}$ structs and one for the $FORK$ structs as global parameters. We will initialize all the required fields here.

Then we will create a function, $\small{philosopher\_simulate}$, where we will pass the $\small{PHILOSOPHER}$ struct as a parameter. This function will then run the above process for the philosopher and be called from every thread.

## PART B

We now also need $1$ of the $2$ available sauce bowls to eat. Also any philosopher can pick up any bowl. Thus, we will use semaphores to implement this on both versions of the previous part. 

Thus, a philosopher will first try to acquire both forks and then the sauce bowl. This ensures there is no deadlock as every philosopher will first ensure that he has both forks before trying to acquire the sauce bowl.

#### <u>IMPLEMENTATION</u>

We need to add another struct to our code, $\small{BOWL}$, which will have the semaphore for the bowl. We will then add another field to the $\small{PHILOSOPHER}$ struct, which will be the reference to the semaphore in the $\small{BOWL}$ struct. We also define another magic number, $\small{BOWL\_CNT}$, which will be the number of sauce bowls available. 

Again, we will use another global array to store the initialized $\small{BOWL}$ structs. These will then be used while simulating the philosophers from every thread.