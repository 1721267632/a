#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>

int main(int arg,char **argv)
{
  int fd;
  if((fd=open("example.txt",O_CREAT|O_EXCL,S_IRUSR|S_IWUSR))==-1)
  {
     perror("open");
  }
  else
  {
     printf("creat file success\n");
  }
  close(fd);
  return 0;
}
