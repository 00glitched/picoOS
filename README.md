# README

## Install and deps
### install
1 - Clone this repo

```git clone this-repo```

2 - Clone pico-sdk inside of repo or auto-install deps

```git clone pico-sdk-repo``` (or download stable version)

3 - Install pico-sdk deps

```sudo apt install pico-sdk-deps```

4 - Make all automaticly

```./deps.sh``` (needs configure variable pkg_MANAGER)

### Run

1 - doall.sh makes all automatically (deps + build)

```./doall.sh```

2 - only build

```./build.sh```

3 - (extra) inside of .bashrc (some code-editors use it to detect libraries)

```source "the/path/to/picoOS/env.sh"``` (pico-sdk path)

## Structure
- main: bootstrap / initializer (as loop)
- kernel: core
- sched: task exec. core / task manager
- HAL: hardware layer
- drivers: peripherics controllers (calls HAL)
- bin: applications (calls drivers)
- term: user input app (calls HAL-UART)

## ToDo list
- [ ] boot main
- [ ] kernel + scheduler
- [x] hardware abstraction layer
    - [x] gpio
    - [ ] pwm
    - [ ] pio
    - [ ] adc
    - [x] uart
    - [ ] spi
    - [ ] i2c
    - [x] timer
- [ ] configuration system
- [ ] basic drivers
    - [ ] led
    - [ ] cmd
- [x] basic applications
    - [ ] blink
    - [ ] term
- [ ] multi-core execution
    - [ ] core0
    - [ ] core1
- [ ] multi-thread


## Implemented drivers and apps
- [x] blink - app
    - builtin led blink app

- [x] led - driver
    - led ON/OFF driver

- [ ] term - app
    - command line interface app

- [ ] cmd - driver
    - rx/tx serial data driver
