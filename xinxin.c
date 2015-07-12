    #include <stdio.h>  
    #ifdef _WIN32  
    #include <windows.h>  
    #define mysleep(n) Sleep(n*1000)   
    #else  
    #include <unistd.h>  
    #define mysleep(n) sleep(n)  
    #endif  
    int main()  
    {  
        int i;  
        for (i = 1; i <= 100; ++i)  
        {  
            printf("=");  
        }  
        fflush(stdout);  
        for (i = 1; i <= 100; ++i)  
        {  
            printf("\b");  
        }  
        for (i = 1; i <= 100; ++i)  
        {  
            printf(">");  
            fflush(stdout);  
            mysleep(1);  
        }  
        printf("\n");  
        return 0;  
    }  
