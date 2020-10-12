#include<stdio.h>
#include<time.h>
#include<string.h>
#include<sys/stat.h>
int main(int argc,char *args[])
{
    time_t t;   
    time(&t);
    if(strcmp(args[1],"-u")==0)
    {
    struct tm *ptm = gmtime(&t);  
    printf("UTC time: %s", asctime(ptm));
    }
    else if(strcmp(args[1],"-r")==0)
    {
    for(int i=2;i<argc;i++)
    {
        struct stat filestat; int status=stat(args[i],&filestat) ; 
        if(status==0)printf("File modify time for %s is %s",args[i],ctime(&filestat.st_mtime));
        else printf("error opening file %s\n",args[i]);
    }
    }
    else printf("%s", ctime(&t));
    return 0;
}