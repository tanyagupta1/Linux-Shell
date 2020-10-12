#include <stdio.h> 
#include<stdlib.h>
#include<string.h>
#include <sys/types.h> 
#include <dirent.h> 
#include <unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
int main(int argc,char *argv[])
{ 
    int fd, i;
    char *c = (char *) calloc(10, sizeof(char)); 
    
    
    for (i = 2; i < argc; i++) 
    {   
        struct stat fileStat;
        if(stat(argv[i],&fileStat)==-1){perror("error"); continue;}
        if(S_ISDIR(fileStat.st_mode)) {printf("Error:This type is directory\n");continue;}

        
        fd = open(argv[i],O_RDONLY);           
        if(fd < 0) { perror("open error"); continue;}
        
        
        
        
        if(strcmp(argv[1],"-n")==0)  
        {         
        int newl='\n'; int spc='\t';
        int j=1;
        
         while(read(fd,c,1))    
       
        {
            if(j==1) {printf("%d ",j);j++;}
            printf("%c",c[0]);
            if(c[0]=='\n') { printf("%d ",j); j++;}
        }
        
        printf("\n");
        close(fd); 
        }
        else if(strcmp(argv[1],"-E")==0)  
        {  

        int newl='\n'; int spc='$';
       
        while(read(fd,c,1))    
        {   
         
        if(c[0]=='\n') {  write(STDOUT_FILENO,&spc,1); }      
        write(STDOUT_FILENO,c,1);  
        }  
        write(STDOUT_FILENO,&spc,1); 
        write(STDOUT_FILENO,&newl,1); 
        close(fd); 
        }
        else
        {
        int newl='\n';
        while(read(fd,c,1))    write(STDOUT_FILENO,c,1);  
        write(STDOUT_FILENO,&newl,1); 
        close(fd); 
        }
                                     
    }
    return 0;
}