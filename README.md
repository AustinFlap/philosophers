# philosophers

`Philosophers` is a program using `threads` and `mutexs`. 

One or more `philosophers` sit at a round table. The `philosophers` alternatively `eat`, `think`, or `sleep`.
While they are eating, they are not thinking nor sleeping; while thinking, they are not eating nor sleeping;
and, of course, while sleeping, they are not eating nor thinking.

There are also `forks` on the table. There are as many `forks` as `philosophers`.
A `philosopher` takes their `right` and their `left` `forks` to `eat`, one in each hand.
When a `philosopher` has finished eating, they put their `forks` back on the table and start sleeping. Once awake, they start thinking again.

The simulation stops when a philosopher dies of starvation.

Every philosopher needs to eat and should never starve. Philosophers don’t speak with each other. Philosophers don’t know if another philosopher is about to die. Philosophers should avoid dying !

## Use

The `philosopher` program work as follows : 
`./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]`

`Number_of_philosophers` : The number of `philosophers` and also the number of `forks`.

`time_to_die` (in milliseconds) : If a philosopher didn’t start eating `time_to_die` milliseconds since the beginning of their last meal or the beginning of the simulation, they die.

`time_to_eat` (in milliseconds) : The time it takes for a `philosopher` to `eat`. During that time, they will need to hold two `forks`.

`time_to_sleep` (in milliseconds) : The time a `philosopher` will spend sleeping.

`number_of_times_each_philosopher_must_eat` (optional argument) : If all `philosophers` have eaten at least `number_of_times_each_philosopher_must_eat times`, the simulation stops. If not specified, the simulation stops when a `philosopher` dies.

<img width="325" alt="Capture d’écran 2022-01-29 à 13 38 51" src="https://user-images.githubusercontent.com/56319429/151661374-85ccbe37-75a6-43f5-9fb7-5e8f6ae03673.png">

