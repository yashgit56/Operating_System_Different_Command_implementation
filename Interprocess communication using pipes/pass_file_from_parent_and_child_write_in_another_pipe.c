#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>


int main() {
    int pipe1fds[2] , pipe2fds[2] ; 

    int returnstatus1 = pipe(pipe1fds) , returnstatus2 = pipe(pipe2fds) ;

    if(returnstatus1 == -1){
        perror("Pipe creation failed") ;
        return 1 ;
    }
    if(returnstatus2 == -1){
        perror("Pipe creation failed") ;
        return 1 ;
    }

    int n = fork() ;
    if(n == -1){
        perror("Fork failed") ;
        return 1 ;
    }

    if(n == 0){
        close(pipe1fds[1]) ;
        close(pipe2fds[0]) ;

        char filename[50] ;
        int bytes = read(pipe1fds[0], filename, sizeof(filename)) ;
        
        if(bytes > 0){
            filename[bytes] = '\0' ;

            int fild_fd = open(filename, O_RDONLY) ;

            if(file_fd != -1){
                char buffer[1024] ;
                int file_bytes ;

                while((file_bytes = read(file_fd, buffer, sizeof(buffer))) > 0){
                    write(pipe2fds[1],buffer,file_bytes) ;
                }
                close(fild_fd) ;
            }
            else{
                perror("child failed to open the file") ;
            }

         }
        close(pipe1fds[0]) ;
        close(pipe2fds[1]) ;
    }
    else{
        close(pipe1fds[0]) ;
        close(pipe2fds[1]) ;

        char filename[] = "sample.txt" ;
        write(pipe1fds[1],filename,sizeof(filename)) ;
        wait(NULL) ;

        char buffer[1024] ;
        int bytes ;

        while((bytes = read(pipe2fds[0],buffer,sizeof(buffer))) > 0){
            write(1,buffer,sizeof(buffer)) ;
        }
        close(pipe1fds[1]) ;
        close(pipe2fds[0]) ;
    }
    
    return 0 ;
}