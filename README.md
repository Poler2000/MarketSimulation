# Market Simulation
## Table of contents
* [General info](#general-info)
* [Install](#install)

## General info
This is a very simple supply-demand simulation. It consists of customers, who are willing to buy products according 
to their needs and budget, as well as companies producing these products. Market adjust prices according to current supply and demand. 
Internally, simulation uses multiple threads running concurrently and interacting in (hopefully) safe way.

## Install
You can use for example something like:

```
$ https://github.com/Poler2000/MarketSimulation
$ cd MarketSimulation
$ mkdir build && cd build
$ cmake .. && make
```

You can run simulation like:
```
$ ./MarketSimualtion $numOfProducts $numOfCompanies $numOfCustomers
```
You will find more configuration options in include/Configuration.h file, so feel free to experiment.