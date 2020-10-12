#include <stdio.h> 
#include<stdlib.h>
#include<string.h>
#include <sys/types.h> 
#include <dirent.h> 
#include <unistd.h>
#include<errno.h>
int main(int argc, char *args[])
{
for(int i=2;i<argc;i++)
{  if(strcmp(args[1],"-f")==0) 
      {
        if(unlink(args[i])!=0 &&(errno==21)) perror("remove error");
      }
   else if(strcmp(args[1],"-i")==0)
   {
         printf("Delete file %s ?[Y/N]:",args[i]);
         char c[10]; scanf("%s",c); fflush(stdin);
         if(c[0]=='Y') 
         {
            if (unlink(args[i]) == 0) printf("Deleted successfully\n"); 
            else perror("Error");   
         }
         else printf("Not deleted \n");
   }
   else
   {
    
   if (unlink(args[i]) == 0) printf("Deleted successfully\n"); 
   else perror("Error"); 
   }
} 
printf("\n");
return 0;
}