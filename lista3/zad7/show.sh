#!/bin/bash

nice -n 10 ./m1.sh & ./m2.sh &



# Komenda 'nice -n 10 ./m1.sh' obniza priorytet procesu o 10. Wykorzystane
#  wywolania powyzej uruchamia dwa skrypty jednoczesnie zwiekszajac liczbe
# nice dla pierwszego skryptu o 10. Powoduje to, ze przy wywolaniu bez
# uzycia nice to, ktory proces skonczy pierwszy jest rozne. W przypadku,
# gdy jednak zasosujemy nice skrypt dwa wykona sie szybciej. Oba skrypty
# prowadza te same obliczenia. Roznia sie tylko wyswietlana wiadomoscia
# na koniec pracy.
