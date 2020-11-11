#include <stdio.h>
#include <time.h>
#include <unistd.h>


int main() {

  struct timespec time,time2;

  time.tv_sec=0;
  time.tv_nsec=100L;
  
  for (int i=0;;++i){
    nanosleep(&time,&time2);
  }

  return 0;
}


/*
Po dodaniu nanosleep() zużycie procesora spadło z 99,9% na około 14%.
Aby zwiększyć częstotliwość odświezania programu top należy nacisnąć podczas
jego działania 'd' na klawiaturze. Spowoduje to, że program będzie chciał
od nas nową wartość odświeżania. Domyślnie jest to raz na 3 sekundy.
*/
