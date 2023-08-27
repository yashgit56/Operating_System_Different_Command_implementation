#include <stdio.h>
#include <unistd.h>

int main() {
    int pipefds[2] ;

    int returnstatus = pipe(pipefds) ;

    if(returnstatus == -1){
        perror("Pipe creation failed") ;
        return 1 ;
    }

    printf("Read file descriptor is: %d and write file descriptor is: %d",pipefds[0], pipefds[1]) ;
    
    return 0 ;
}