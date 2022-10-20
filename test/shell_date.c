#include<time.h>
#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
int main(int argc, char* argv[])
{
    printf("%s\n",argv[0]);
    struct stat filestat;
    stat(argv[2],&filestat);
    struct tm *local;
    time_t t;
    t=time(NULL);
    if(!strcmp(argv[0],"0"))
        printf("%s", ctime(&t));
    else if(!strcmp(argv[0],"1"))
        printf("%s", asctime(gmtime(&t)));
    else if(strcmp(argv[0],"2"))
        printf("%s",ctime(&filestat.st_mtime));
    // else if(argv[1][0]=='0')
    //     printf("%s", ctime(&t));
    return 0;
}
