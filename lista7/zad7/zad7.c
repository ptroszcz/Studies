#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define RANDOMNR 1000000
#define THREADNR 10

void *thread_pi(void *pi) {
  double* result;
  result=(double *)pi;
  double circle=0;
  for (int i=0;i<RANDOMNR;++i) {
    double x=drand48();
    double y=drand48();
    /*zalozono ze dlugosc boku kwadratu jest rowna 1*/
    if(((0.5-x)*(0.5-x)+(0.5-y)*(0.5-y))<0.25)
      circle++;
  }
  *result=4*circle/RANDOMNR;
  pthread_exit(NULL);
}

int main(){

  pthread_t id[THREADNR];
  int fail;
  double resultpi[THREADNR];

  for(long i=0;i<THREADNR;++i) {
    printf("Creating thread %ld.\n",i);
    fail=pthread_create(&id[i], NULL, thread_pi,(void *) &resultpi[i]);
    if (fail) {
      fprintf(stderr,"Nie poprawne stworzenie wątku.\n");
      return -1;
    }
  }

  double meanpi=0;
  for(int i=0; i<THREADNR;++i){
    pthread_join(id[i], NULL);
    printf("Watek numer %d zwrocil wartosc pi jako: %f\n",i,resultpi[i]);
    meanpi+=resultpi[i];
  }
  meanpi=meanpi/THREADNR;
  printf("Srednie pi wynosi: %f\n",meanpi);

  pthread_exit(NULL);
}
