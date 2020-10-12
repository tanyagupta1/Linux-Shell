#include <stdio.h> 
#include <dirent.h> 
#include <unistd.h>
#include<string.h>
#include<sys/types.h>
#include<stdlib.h>
int main(int argc,char *argv[]) 
{   //printf("hi");
	char *cwd=(char*)malloc(4096*sizeof(char));
    if(strlen(argv[2])==0)
	{
	if (getcwd(cwd, 4096*sizeof(cwd)) == NULL)
    {perror("getcwd() error");return EXIT_FAILURE;}
	}

	else
	{
		strcpy(cwd,argv[2]);
	}
	
   // else
     // printf("%s\n", cwd);
    //free(cwd);
	//printf("current dir is %s",cwd);
	//char * curr_dir;
	//curr_dir=getenv("PWD");
	struct dirent *de; 
	//DIR *dr = opendir("."); 
	char name[100]; name[0]='\0';
	DIR *dr=opendir((const char*)cwd);

	if (dr == NULL) 
	{ 
		perror("open error:");
		return 0; 
	} 

	if(strcmp(argv[1],"-i")==0)
	{
		while ((de = readdir(dr)) != NULL) 
		printf("%lu %s \n",de->d_ino,de->d_name); 
        printf("\n") ;  
	}
	else if(strcmp(argv[1],"-a")==0)
	{
		while ((de = readdir(dr)) != NULL) 
		printf("%s \n",de->d_name); 
        printf("\n") ;  

	}
	 else
	 {
		while ((de = readdir(dr)) != NULL) 
		{
		strcpy(name,de->d_name);
		if(name[0]=='.');
		else printf("%s \n",de->d_name); 
		}
        printf("\n") ;
	 }
	 

	closedir(dr);	 
	//return 0; 
	exit(0);
}