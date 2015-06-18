#include<stdio.h>
#include<stdlib.h>

int main(void)
{
  FILE *fp;
  char p[15];
  fp=fopen("example.txt","at+");
  fread(p, 10, 1, fp);
  printf("%s\n",p); 
}
