#include <stdio.h>
#include <pthread.h>

#define THREADNR 7

void *thread_hello(void *id) {
  long lid=(long)id;
  printf("Hello SCR. Written by thread %ld, ID=%ld\n",lid,pthread_self());

  pthread_exit(NULL);
}

int main(){

  pthread_t id[THREADNR];
  int fail;

  for(long i=0;i<THREADNR;++i) {
    printf("Creating thread %ld.\n",i);
    fail=pthread_create(&id[i], NULL, thread_hello,(void *)i);
    if (fail) {
      fprintf(stderr,"Nie poprawne stworzenie wątku.\n");
      return -1;
    }
  }

  for(int i=0; i<THREADNR;++i)
    pthread_join(id[i], NULL); //czekanie az wszystkie watki sie zakoncza

  pthread_exit(NULL);
}
