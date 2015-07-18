/*************************************************************************
	> File Name: my_file.c
	> Author: 
	> Mail: 
	> Created Time: 2015年07月18日 星期六 15时22分06秒
 ************************************************************************/

#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
    int fd;
    int i = 0;
    char a[10]="abcde";

    if((fd = open("123.txt",O_RDWR|O_CREAT,S_IRWXU)) == -1)
    {
        printf("create error!\n");
        exit(1);
    }

    while(1)
    {
        if(a[i] == '\0')
        {
            break;
        }
        write(fd, &a[i], 1);
        i++;
    }

    close(fd);
    return 0;
}
