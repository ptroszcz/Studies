#!/bin/bash

Mask=$1

Days=$2

Tar=$3

find $HOME -mtime -$Days -name $Mask -print0 | tar -cvf $Tar --null -T -
