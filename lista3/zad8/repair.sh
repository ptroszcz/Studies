#!/bin/bash

for i in $(pgrep danger.sh)
do
    kill -9 $i
done
