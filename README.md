# README

## Install and deps
### install
1 - Clone this repo

```git clone this-repo```

2 - Clone pico-sdk inside of repo or auto-install deps

```git clone pico-sdk-repo``` (or download stable version)

3 - Install pico-sdk deps

```sudo apt install```

### Run

1 - doall.sh makes all automatically (install + build)

```./doall.sh```

2 - only build

```./build.sh```

## Structure
- main: bootstrap / initializer
- kernel: core
- sched: task exec. core / task manager
- HAL: hardware layer
- drivers: peripherics controllers (calls HAL)
- bin: applications (calls drivers)
- term: user input app (calls HAL-UART)
