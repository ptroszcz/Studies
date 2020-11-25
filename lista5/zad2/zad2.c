#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

#define BUF_SIZE 14

int main(int argc, char *argv[]){

  int potok_fd[2];
  int des;
  char bufor[BUF_SIZE];
  if (pipe(potok_fd)<0) {
    fprintf(stderr,"Nieudalo sie utworzyc potoku.\n");
    return -1;
  }

  int pid=fork();
  if (pid>0) {
    //rodzic
    close(potok_fd[0]);
    if ((des=open(argv[1],O_RDONLY))<0){
      fprintf(stderr,"Nie udalo sie otworzyc pliku.\n");
      return -1;
    }
    int temp;
    while ((temp=read(des,bufor,BUF_SIZE))>0)
      write(potok_fd[1],bufor,temp);
    close(des);
    sleep(2);           /*na potrzeby sprawdzenia kiedy wyswietla sie obraz*/
    close(potok_fd[1]);
    printf("Proces rodzica zamknal potok.\n");
    sleep(2);
  }
  else if (pid==0){
    //potomek
    close(potok_fd[1]);
    close(0);
    dup(potok_fd[0]);
    execlp("display","display","-",NULL);
  }
  else {
    fprintf(stderr,"Nieudalo sie utworzyc procesu potomnego.\n");
    return -1;
  }
  close(potok_fd[1]);
  close(potok_fd[0]);
  return 0;
}


/*
Obraz wyswietlany jest przez procesn potomka po tym jak proces nadrzedny zamknie potok
 */
