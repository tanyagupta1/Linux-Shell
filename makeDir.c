#include <stdio.h> 
#include<stdlib.h>
#include<string.h>
#include <sys/types.h> 
#include <dirent.h> 
#include <unistd.h>
#include<sys/stat.h>
int main(int argc, char *args[])
{

for(int i=2;i<argc;i++)
{
if(strcmp(args[1],"-v")==0)
{
if(mkdir(args[i],0777)==0) printf("created %s\n",args[i]);
//else printf("Unable to create the directory %s\n",args[i]); 
else perror("error:directory not made");
}
else if(strcmp(args[1],"-m")==0)
{

   int perm=strtol(args[2], NULL, 8); 
   if(i==2) continue;
   else
   {
      if(mkdir(args[i],perm)==0) printf("created %s\n",args[i]);
      //else printf("Unable to create the directory %s\n",args[i]); 
      else perror("error:directory not made");
   }
   

}
else 
{
   if(mkdir(args[i],0777)==0) ;
  // else printf("Unable to create the directory %s\n",args[i]); 
  else perror("error:directory not made");

} 
}
printf("\n");
return 0;
}