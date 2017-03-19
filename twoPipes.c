#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
//Leslie McCarthy DNET3


int main(){
 int status;
 pid_t pid = getpid();
 pid_t childpid, childpid2, childpid3;
 int c1Toc3[4];
 pipe(c1Toc3); //First pipe
 pipe(c1Toc3 + 2); //second pipe
 
 
 
 printf("STARTING PROCESS PID %d\n",pid);

 // Add the code for the two children here
  
    childpid = fork();   
    
    if (childpid < 0){
        perror("fork failed");
        exit(1);
    }
    
    else if (childpid == 0){
       
        dup2(c1Toc3[1], STDOUT_FILENO);
        close(c1Toc3[0]);
        close(c1Toc3[1]);
        close(c1Toc3[2]);
        close(c1Toc3[3]);
        
        execlp("ps", "ps", "-ef",(char *)0);      
        
        exit(0);
    }
    
    else{
        childpid2 = fork();
        if (childpid2 < 0){
            perror("fork failed for child 2");
            exit(1);
        }
        
        else if (childpid2 == 0){                
            dup2(c1Toc3[0], STDIN_FILENO);
            dup2(c1Toc3[3], STDOUT_FILENO);
            close(c1Toc3[0]);
            close(c1Toc3[1]);
            close(c1Toc3[2]);
            close(c1Toc3[3]);
            execlp("grep","grep","root",(char *)0);  
        
        }
        
        else{
            childpid3 = fork();
            
            if (childpid3 < 0){
            perror("fork failed for child 3");
            exit(1);
            }
        
            else if (childpid3 == 0){         
            
            dup2(c1Toc3[2], STDIN_FILENO);
           
            close(c1Toc3[0]);
            close(c1Toc3[1]);
            close(c1Toc3[2]);
            close(c1Toc3[3]);   
             execlp("sort","sort","-n","-k 4",(char *)0);
            exit(0);
            }  
        }
    }  
     
    close(c1Toc3[0]);
    close(c1Toc3[1]);
    close(c1Toc3[2]);
    close(c1Toc3[3]);
   
    for (int i = 0; i < 3; i++)//Wait for three children to finish.
        wait(NULL);
        //wait(NULL);
        //wait(NULL);
         
   
    printf("PARENT: PROCESS Waiting on children to complete\n");            
    
    printf("\nFinal Print Statement before exit\n");
       
        
 exit(0);
 
}