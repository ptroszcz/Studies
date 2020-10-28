#!/bin/bash

trap "echo przechwycony" {1..15}

while :
do
    date
    sleep 1
done

