#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h> 
#include <unistd.h> 
#define MAX 1000
char path[4096]; char lastcd[1000];
extern void echo(char *token),pwd(char *token),cd(char* token),ls(char *token),rm(char * token),mk(char* token),date(char * token),catFile(char *token);
extern int hist(char *token);
int main()
{
  char buf[1000];
  char *history[500]; int command=0; lastcd[0]='\0';
  getcwd(path, 4096*sizeof(char)); strcpy(lastcd,path);
  while(fgets(buf,MAX,stdin))
  {
      
      if(buf[strlen(buf)-1]=='\n')buf[strlen(buf)-1]='\0';
      history[command]=calloc(strlen(buf)+2,sizeof(char));
      strcpy(history[command],buf);
      command++;
      if(strcmp(buf,"exit")==0) exit(0);
      else 
      {
          char * token=strtok(buf," ");
	        if(strcmp(token,"echo")==0) echo(token);
          else if(strcmp(token,"history")==0) 
          {  
            int argu=hist(token);
            if(argu==-1);
            else if(argu==100) command=0;
            else if (argu==0)for (int i=0;i<command;i++)printf("%d %s\n",i+1,history[i]);
            else for (int i=0;i<((command>argu)?argu:command);i++)printf("%d %s\n",i+1,history[command-1-i]);
          }
          else if(strcmp(token,"pwd")==0) pwd(token);
          else if(strcmp(token,"cd")==0) cd(token);

          else if(strcmp(token,"ls")==0) ls(token);
          else if(strcmp(token,"rm")==0) rm(token);
          else if(strcmp(token,"mkdir")==0) mk(token);
          else if(strcmp(token,"date")==0) date(token);
          else if(strcmp(token,"cat")==0) catFile(token);
          else printf("command %s not found!\n",token);
          
      }
      
    }
    for(int i=0;i<command;i++)free(history[i]);

    return 0;
}