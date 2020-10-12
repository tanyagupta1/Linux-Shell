#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h> 
#include<sys/wait.h>
#include <unistd.h> 
#include <dirent.h> 
#include<sys/stat.h>
#include<fcntl.h>
extern char path[]; extern char lastcd[];
void echo(char*token)
{

char *ans= (char*) malloc(100*sizeof(char));
int stringLeft=100;
int arrSize=100;
ans[0]='\0';
token=strtok(NULL," "); 
int newlineFlag=0; int help=0;
		while(token) 
		{  
      if(strcmp(token,"-n")==0){newlineFlag=1;}
      else if(strcmp(token,"-E")==0);
      else if(strcmp(token,"--help")==0) help=1;
			else
      {
        if(stringLeft<strlen(token))
        { 
          ans=realloc(ans,(arrSize+strlen(token)+1)*sizeof(char));
          arrSize+=strlen(token)+1;
          stringLeft+=strlen(token)+1;
        }

        strcat(ans,token); strcat(ans," ");
        stringLeft-=strlen(token);
			
      }
      token=strtok(NULL," "); 
		}
    if(help)
    {
      printf("Echo -E <string> -> prints string with newline and disabled escape sequence interpretation\necho -n <string>-> prints the string without the leading newline\n");
      return;
    }
		if(!newlineFlag)printf("%s\n",ans);
    else printf("%s",ans);
		free(ans);
}
void pwd(char * token)
{
token=strtok(NULL," "); 
int i=0;
int isL=1;
while(token)
{
i++; 
if((strcmp(token,"-P")==0)||(strcmp(token,"-L")==0)){if(strcmp(token,"-P")==0) isL=0;}
else {printf("invalid flag\n"); return;}
token=strtok(NULL," ");
}
if(i>1) {printf("too many arguments\n"); return;}
if(!isL)
{
    char *cwd=(char*)malloc(4096*sizeof(char));
    if (getcwd(cwd, 4096*sizeof(cwd)) == NULL)perror("getcwd() error");
    else printf("%s\n", cwd);
    free(cwd);
}
else 
{
    printf("%s\n",lastcd);
}
}


void cd(char*token)
{
char *ans= (char*) malloc(400*sizeof(char));
ans[0]='\0'; int isL=1; 
token=strtok(NULL," "); 
int i=0;
		while(token) 
		{  
      i++;
            if(strcmp(token,"-L")==0);
            else if(strcmp(token,"-P")==0)isL=0;
			
            else strcpy(ans,token);
			token=strtok(NULL," "); 
		}
    if(i>2){printf("error: too many arguments for CD\n"); return;}
    if((strlen(ans)==0)||(strcmp(ans,"~")==0))
    {
      
      if(chdir(getenv("HOME"))!=0) perror("");
      else 
      {
          char *cwd=(char*)malloc(4096*sizeof(char));
           getcwd(cwd, 4096*sizeof(cwd));
           strcpy(lastcd,cwd);
      }

    } 
	else
    {
      
      if(isL)        //isL
      {
        if(ans[0]=='/')  
        {
            
             struct stat buf; int x;
             x = lstat (ans, &buf);
             if(x<0){perror("error");return;}
            if (S_ISLNK(buf.st_mode)) 
            {
               
                if(chdir(ans)!=0) perror("CD Failure");
                else strcpy(lastcd,ans);
            }

            else if (S_ISREG(buf.st_mode)||S_ISDIR(buf.st_mode)) isL=0;
            
        }
        else
        {
            
            if(strcmp(ans,".")==0 || (strcmp(ans,"./")==0));
            else if(strcmp(ans,"..")==0)
            {   
                char back[1000]; back[0]='\0';
                strcpy(back,lastcd);
                for(int i=strlen(back)-1;i>=0;i--)
                {
                    if(back[i]=='/'){back[i]='\0'; break;}
                    
                    else back[i]='\0';
                }

                if(chdir(back)!=0){perror("error");}
                else strcpy(lastcd,back);
            }
            else
            {
            char *cwd=(char*)malloc(4096*sizeof(char));
            getcwd(cwd, 4096*sizeof(cwd)); strcat(cwd,"/");
            strcat(cwd,ans);

            struct stat buf; int x;
             x = lstat (cwd, &buf);
             if(x<0){perror("error");return;}
            if (S_ISLNK(buf.st_mode)) 
            {
                if(chdir(cwd)!=0) perror("CD Failure");
                //else strcpy(lastcd,cwd);
                else
                {
                 
                  strcat(lastcd,"/"); strcat(lastcd,ans);
                }
                
            }

            else if (S_ISREG(buf.st_mode)||S_ISDIR(buf.st_mode)) //isL=0;
            {
              if(chdir(cwd)!=0) perror("CD Failure");
                //else strcpy(lastcd,cwd);
                else
                {
                 
                  strcat(lastcd,"/"); strcat(lastcd,ans);
                }
            }
            }

        }
        
      }
      if(!isL)
      {
       if(chdir(ans)!=0) perror("CD Failure");
       else 
       {
           char *cwd=(char*)malloc(4096*sizeof(char));
           getcwd(cwd, 4096*sizeof(cwd));
           strcpy(lastcd,cwd);
       }
      }
      
      
    } 
	
    free(ans);
}

int hist(char *token)
{
int number=0;
token=strtok(NULL," "); 
int i=0;
		while(token) 
		{  i++;
      if(strcmp(token,"-c")==0) return 100;
		  number=atoi(token);
      if(number ==0){ printf("Argument should be an integer\n"); return -1;}
			token=strtok(NULL," "); 
		}
    if(i>1) {printf("Too many arguments\n"); return -1;}
  return number;

}

void ls(char *token)
{
    int status;
    char ar[10]; ar[0]='\0';char dir[1000];dir[0]='\0'; int i=0;
    token=strtok(NULL," ");
    while(token)
    {
      i++;
      if(strcmp(token,"-i")==0)strcpy(ar,token);
      else if(strcmp(token,"-a")==0) strcpy(ar,token);
      else strcpy(dir,token);
      token=strtok(NULL," "); 
    }
     //printf("args[0] is %s",dir);
    pid_t pid=fork(); if(pid<0){perror("fork error"); return ;}
    if(pid>0) wait(&status);
    else
    {
        char *args[4];
        args[0]=calloc(100,sizeof(char));args[1]=calloc(100,sizeof(char));args[2]=calloc(1000,sizeof(char));
        args[3]=calloc(100,sizeof(char));
        strcpy(args[0],path);strcat(args[0],"/ls");strcpy(args[1],ar);strcpy(args[2],dir);args[3]=NULL;
        //printf("args[0] is %s",args[0]);
        //execvp(args[0],args);
        if(execvp(args[0],args)<0) 
        {
          perror("error");
          exit(EXIT_FAILURE);
        }
    }
    
}


void rm(char *token)
{  
    int status;
    token=strtok(NULL," ");
    char *args[100];
    int i=0;
    args[i]=calloc(100,sizeof(char));
    strcpy(args[i],path);strcat(args[i],"/rm"); i++;
    //strcpy(args[i],"/home/tanya/tanya/cppCode/a1/a1.2/rm"); i++;
    args[i]=calloc(10,sizeof(char));
    strcpy(args[i]," "); i++;

    while(token)
    {
      if(strcmp(token,"-f")==0) strcpy(args[1],token);
      else if (strcmp(token,"-i")==0) strcpy(args[1],token);
      else
      {
      args[i]=calloc(100,sizeof(char));
      strcpy(args[i],token);  
      i++;
      }
      token=strtok(NULL," ");
    }
    if(i==2){printf("no filename specified\n"); return;}
    

    args[i]=calloc(10,sizeof(char));
    args[i]=NULL; i++;

    //for(int j=0;j<i;j++) printf("%s",args[j]);
    pid_t pid=fork(); if(pid<0){perror("fork error"); return ;}
    if(pid>0) 
    {
        wait(&status);
       for(int j=0;j<i;j++) free(args[j]);
       
    }
    else 
    {
           //execvp(args[0],args);
           if(execvp(args[0],args)<0) 
        {
          perror("error");
          exit(EXIT_FAILURE);
        }

    }  
}

void mk(char *token)
{  
    int status;
    token=strtok(NULL," ");
    char *args[100];
    int i=0;
    args[i]=calloc(100,sizeof(char));
    strcpy(args[i],path);strcat(args[i],"/makeDir"); i++;
    //strcpy(args[i],"/home/tanya/tanya/cppCode/a1/a1.2/makeDir"); i++;
    args[i]=calloc(10,sizeof(char));
    strcpy(args[i]," "); i++;


    while(token)
    {
      if(strcmp(token,"-v")==0) strcpy(args[1],token);
      else if (strcmp(token,"-m")==0) strcpy(args[1],token);
      else
      {
      args[i]=calloc(100,sizeof(char));
      strcpy(args[i],token);  
      i++;
      }
      token=strtok(NULL," ");
    }
    if(i==2) {printf("missing arguments for directory name \n"); return ;}
    if(i==3 && strcmp(args[1],"-m")==0) {printf("insufficient arguments for -m \n"); return ;}
    args[i]=calloc(10,sizeof(char));
    args[i]=NULL; i++;
    pid_t pid=fork(); if(pid<0){perror("fork error"); return ;}
    if(pid>0) 
    {
        wait(&status);
       for(int j=0;j<i;j++) free(args[j]);
       
    }
    else   
    {
      //execvp(args[0],args);
      if(execvp(args[0],args)<0) 
        {
          perror("error");
          exit(EXIT_FAILURE);
        }
    }
}
void date(char *token)
{
    int status;
    token=strtok(NULL," ");
    char *args[100];
    int i=0;
    args[i]=calloc(100,sizeof(char));

    strcpy(args[i],path);strcat(args[i],"/dateTime"); i++;
    //printf("args[i] is %s",args[0]);
    //strcpy(args[i],"/home/tanya/tanya/cppCode/a1/a1.2/dateTime"); i++;
    args[i]=calloc(10,sizeof(char));
    strcpy(args[i]," "); i++;
    while(token)
    {
      if(strcmp(token,"-u")==0) strcpy(args[1],token);
      else if(strcmp(token,"-r")==0) strcpy(args[1],token);
      else
      {
      args[i]=calloc(100,sizeof(char));
      strcpy(args[i],token);  
      i++;
      }
      token=strtok(NULL," ");
    }
    //if(i>3) {printf("too many arguments\n"); return;}
    if(i==3 && (strcmp(args[1]," ")==0)){printf("no such flag handled\n"); return;}
    if(i==2 && (strcmp(args[1],"-r")==0)){printf("no file argument given\n"); return;}

    args[i]=calloc(10,sizeof(char));
    args[i]=NULL; i++;
    pid_t pid=fork(); if(pid<0){perror("fork error"); return ;}
    if(pid>0) 
    {
        wait(&status);
       for(int j=0;j<i;j++) free(args[j]);
       
    }
    else  
    {
      if(execvp(args[0],args)<0) 
        {
          perror("error");
          exit(EXIT_FAILURE);
        }

    } //execvp(args[0],args);

}
void catFile(char *token)
{  
    int status;
    token=strtok(NULL," ");
    char *args[100];
    int i=0;
    args[i]=calloc(100,sizeof(char));
    strcpy(args[i],path);strcat(args[i],"/cat"); i++;
    //strcpy(args[i],"/home/tanya/tanya/cppCode/a1/a1.2/cat"); i++;
    args[i]=calloc(10,sizeof(char));
    strcpy(args[i]," "); i++;

    while(token)
    {
      if(strcmp(token,"-n")==0) strcpy(args[1],token);
      else if(strcmp(token,"-E")==0) strcpy(args[1],token);
      else
      {
      args[i]=calloc(100,sizeof(char));
      strcpy(args[i],token);  
      i++;
      }
      token=strtok(NULL," ");
      
    }
    args[i]=calloc(10,sizeof(char));
    args[i]=NULL; i++;
    pid_t pid=fork(); if(pid<0){perror("fork error"); return ;}
    if(pid>0) 
    {
        wait(&status);
       for(int j=0;j<i;j++) free(args[j]);
       
    }
   // else   execvp(args[0],args);
   else
   {
     if(execvp(args[0],args)<0) 
        {
          perror("error");
          exit(EXIT_FAILURE);
        }
   }
   
}

