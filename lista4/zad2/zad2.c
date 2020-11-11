#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>


void handler1(int signal){
  printf("Zlapano sygnal o numerze %d\n", signal);
  exit(signal);
}

void handler2(int signal){
  printf("Zlapano sygnal o numerze %d\n", signal);
}

void handler3(int signal){
  sigset_t x;
  sigemptyset(&x);
  sigaddset(&x, SIGUSR1);
  sigaddset(&x, SIGUSR2);
  sigaddset(&x, SIGALRM);
  sigaddset(&x, SIGTERM);
  sigprocmask(SIG_BLOCK,&x,NULL);
  for(int i=0;i<10;++i){
    printf("Nie dziala jeszcze przez %d\n",10-i);
    sleep(1);
  }
  printf("Kontynuowanie odebrania sygnalu\n");
  sigprocmask(SIG_UNBLOCK,&x,NULL);


}

void handler4(int signal){}

int main() {

 
  signal(SIGTERM,handler1);
  signal(SIGALRM,handler2);
  signal(SIGUSR1,handler3);
  signal(SIGUSR2,handler4);
 
  
  
  for (int i=0;;++i){
    sleep(1);
    printf("Dziala\n");
  }

  return 0;
}


