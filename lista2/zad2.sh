#!/bin/bash

path=$(pwd)/pliki

for mail in $(cat $path/adresy.txt)
do
    cat $path/tresc.txt | mutt -s "Zapytanie ofertowe" $mail -a $path/spec*.pdf
done
