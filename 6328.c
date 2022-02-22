#include <stdio.h> 
 #include <stdlib.h> 
 #include <string.h> 
 #include <sys/types.h> 
 #include <sys/wait.h> 
 #include <unistd.h> 
 #include <signal.h>
char cmd[256];
char *arguments[20];
pid_t pid;

int i;
void readCommand()
{
    printf("shell>>\t");
    fgets(cmd,256,stdin);
    if ((strlen(cmd)>0)&& (cmd[strlen(cmd)-1]=='\n'))
    cmd[strlen(cmd)-1]='\0';
    
   
   
}
void convert(){
      // split string into arguments
    i=0;
    char *parseString;
    
    parseString=strtok(cmd," ");

    while(parseString!=NULL)
    {
        arguments[i++]=parseString;
        parseString=strtok(NULL," ");
    }
    if (!strcmp("&",arguments[i-1])){
    arguments[i-1]=NULL;
    arguments[i]="&";
    }
    else
    arguments[i]=NULL;

}
void log_handle(){
    //signal handler to add log statements
FILE *f;
f=fopen("log.txt","a");
if(f==NULL) perror("Error opening file.");
else fprintf(f,"[LOG] child process terminated.\n");
fclose(f);
}
int main()
{


    signal(SIGCHLD,log_handle);
    while(1)
    {
       
        readCommand();
        if(!strcmp("",cmd))continue;
        
        if(!strcmp("exit",cmd))break;
        convert();
         
       // fork and execute the command
        if(fork()!=0)
        { 
                         // wait for the command to finish if “&” is not present
           wait(NULL);
        printf("faild to create a chile\n");}
        else
        {
            execvp(arguments[0],arguments);
            
        }
       
    }
    return 0;
}