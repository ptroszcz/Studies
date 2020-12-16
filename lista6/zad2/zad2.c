#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MEMORY "memoryfile"

int main(){

  char filename[50];
  int fd_m,fd_f;
  struct stat statfile;
  char *memptr;

  int pid=fork();
  if (pid<0) {
    fprintf(stderr,"Nie udalo sie utworzyc procesu potomnego.\n");
    return -1;
  }
  if (pid==0) {
    execlp("display","display","-update","1","-delay","2","memoryfile", NULL);
  }
  while(1){
    printf("Podaj nazwe pliku\n");
    scanf("%s",filename);
    if ((fd_f=open(filename,O_RDONLY,0))<0){
	fprintf(stderr,"Nie udalo sie otworzyc podanego pliku.\n");
	return -1;
    }
    if ((fd_m=open(MEMORY,O_RDWR,0))<0){
	fprintf(stderr,"Nie udalo sie otworzyc pliku pamieci.\n");
	return -1;
    }
    if (stat(filename,&statfile)<0){
      fprintf(stderr,"Nie udalo sie uzyskac informacji o podanym pliku.\n");
      return -1;
    }
    ftruncate(fd_m, statfile.st_size);
    memptr=(char *)mmap(NULL,statfile.st_size,PROT_READ | PROT_WRITE,MAP_SHARED,fd_m,0);
    read(fd_f,memptr,statfile.st_size);
    msync(memptr,statfile.st_size, MS_SYNC);
    close(fd_m);
    close(fd_f);
    
  }

}
