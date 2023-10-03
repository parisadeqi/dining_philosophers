# dining_philosophers

# About the project

This project is based on the <a href="https://en.wikipedia.org/wiki/Dining_philosophers_problem">Dining Philosophers Problem</a> but with some diffrences which you can find in the subject of this project in the file subject.en.

## Build
You can run this command to build this project
```sh
$ make
```

## Run
You can run this project like this:
```sh
$./philo number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat]
```

here are some examples of how the program should act :
whit this arguments no philosopher should die:
```sh
$./philo 5 800 200 200
```

One philosopher should die (and delay of more than 10ms for death is not acceptable)
```sh
$./philo 4 310 200 100
```

Program should stop after each philosopher has eten at least 7 times
```sh
$./philo 5 800 200 200 7
```
