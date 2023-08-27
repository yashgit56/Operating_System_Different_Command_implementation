#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


int main() {
    int pipefds[2] ;

    int returnstatus = pipe(pipefds) ;

    if(returnstatus == -1){
        perror("Pipe creation failed") ;
        return 1 ;
    }

    int n = fork() ;
    if(n == -1){
        perror("Fork failed") ;
        return 1 ;
    }

    if(n == 0){
        close(pipefds[1]) ;

        char message[50] ;
        read(pipefds[0], message, sizeof(message)) ;
        printf("received message is : %s",message) ;
        close(pipefds[0]) ;
    }
    else{
        close(pipefds[0]) ;

        char message[] = "Hello World" ;
        
        write(pipefds[1],message,sizeof(message)) ;
        close(pipefds[1]) ;
        wait(NULL) ;
    }
    
    return 0 ;
}