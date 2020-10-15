#!/bin/bash

LC_ALL=C

day=$(date +%w)


if [ $day -eq 0 -o $day -eq 6 ]
    then  
        echo "Dzisiaj jest weekend"
    else
        echo "Dzisiaj jest normalny dzien tygodnia"
fi
