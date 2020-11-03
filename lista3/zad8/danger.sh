#!/bin/bash

#Zmieniona wartosc maksymalnej liczby procesow uzytkownika na 500 poleceniem:
#'ulimit -u 500'

while :
do
    echo 1
    ./danger.sh
done


# Jeżeli uruchomimy ten skypt poleceniem './danger.sh' po osiagnieciu
# maksymalnej liczby procesow wystarczy uzyc skrotu Ctrl+C, aby pozabyc
# sie istniejacego problemu. W przypadku wywolania './danger.sh &' napisalem
# skrypt repair.sh. Uruchomienie go w innym terminalu naprawi problem
# nieskonczenie kopiujacego sie skryptu
