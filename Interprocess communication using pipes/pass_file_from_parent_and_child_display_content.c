#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>


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

        char filename[50] ;
        int bytes = read(pipefds[0], filename, sizeof(filename)) ;
        
        if(bytes > 0){
            filename[bytes] = '\0' ;

            int fild_fd = open(filename, O_RDONLY) ;

            if(file_fd != -1){
                char buffer[1024] ;
                int file_bytes ;

                while((file_bytes = read(file_fd, buffer, sizeof(buffer))) > 0){
                    write(1,buffer,file_bytes) ;
                }
                close(fild_fd) ;
            }
            else{
                perror("child failed to open the file") ;
            }

         }
        close(pipefds[0]) ;
    }
    else{
        close(pipefds[0]) ;

        char filename[] = "sample.txt" ;
        
        write(pipefds[1],filename,sizeof(filename)) ;
        close(pipefds[1]) ;
        wait(NULL) ;
    }
    
    return 0 ;
}