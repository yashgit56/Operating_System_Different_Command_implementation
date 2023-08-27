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
        close(pipefds[0]) ;
        char message[] = "Hello World" ;
        write(pipefds[1],message,sizeof(message)) ;
        close(pipefds[1]) ;
    }
    else{
        close(pipefds[1]) ;
        char message[50] ;
        int bytes ;

        wait(NULL) ;
        bytes = read(pipefds[0],message,sizeof(message)) ;
        if(bytes > 0){
            printf("Parent received message: %s",message) ;
        }
        else{
            printf("Failed to receive message") ;
        }
        
        close(pipefds[0]) ;
    }
    
    return 0 ;
}