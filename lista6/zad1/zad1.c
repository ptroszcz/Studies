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
  int fd_m;
  struct stat statfile;
  char *memptr;

  while(1){
    printf("Podaj nazwe pliku\n");
    scanf("%s",filename);
    FILE *file=fopen(filename,"r");
    if ((fd_m=open(MEMORY,O_RDWR,0))<0){
	fprintf(stderr,"Nie udalo sie otworzyc pliku pamieci.\n");
	return -1;
    }
    if (stat(filename,&statfile)<0){
      fprintf(stderr,"Nie udalo sie uzyskac informacji o podanym pliku.\n");
      return -1;
    }
    memptr=(char *)mmap(NULL,statfile.st_size,PROT_READ | PROT_WRITE,MAP_SHARED,fd_m,0);
    ftruncate(fd_m, statfile.st_size);
    int i=0;
    char c;
    while ((c=getc(file))!=EOF)
      memptr[i++]=c;
    close(fd_m);
    fclose(file);
    
  }

}
