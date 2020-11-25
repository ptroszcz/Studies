#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

#define BUF_SIZE 14

int main(int argc, char *argv[]){

  int potok_fd[2], count;
  int des;
  char bufor[BUF_SIZE];
  if (pipe(potok_fd)<0) {
    fprintf(stderr,"Nieudalo sie utworzyc potoku.\n");
    return -1;
  }

  int pid=fork();
  if (pid>0) {
    close(potok_fd[0]);
    if ((des=open(argv[1],O_RDONLY))<0){
      fprintf(stderr,"Nie udalo sie otworzyc pliku.\n");
      return -1;
    }
    int temp;
    while ((temp=read(des,bufor,BUF_SIZE))>0)
      write(potok_fd[1],bufor,temp);
    close(des);
  }
  else if (pid==0){
    close(potok_fd[1]);
    while((count=read(potok_fd[0],bufor,BUF_SIZE))>0){
      printf("#");
      for (int i=0;i<count;++i)
	printf("%c",bufor[i]);
      printf("#\n");
    }
  }
  else {
    fprintf(stderr,"Nieudalo sie utworzyc procesu potomnego.\n");
    return -1;
  }
  close(potok_fd[0]);
  close(potok_fd[1]);

  return 0;
}
