#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>

#define BUF_SIZE 100
#define POTOK "potok1"
/*utworzono potok poleceniem
mknod potok1 p
*/

int main(int argc, char *argv[]){

  int potok_fd;
  char bufor[BUF_SIZE];
  if (argc<=1) {
    printf("Uruchomiono program ze zbyt mala liczba parametrów wywołania\n");
    return -1;
  }
  if ((potok_fd=open(POTOK,O_WRONLY))<0){
    fprintf(stderr,"Nie udalo sie otworzyc potoku nazwanego\n");
    return -1;
  }
  int des;
  for (int i=0;i<argc-1;i++){
    if ((des=open(argv[i+1],O_RDONLY))<0){
      fprintf(stderr,"Nie udalo sie otworzyc pliku podanego jako %d.\n",i+1);
      return -1;
    }
    int temp;
    while ((temp=read(des,bufor,BUF_SIZE))>0)
      write(potok_fd,bufor,temp);
    close(des);
    sleep(2);
  }
  
  close(potok_fd);

  return 0;
}


/*potok czytano w osobnym terminalu poleceniem
tail -c +1 -f potok1
*/
