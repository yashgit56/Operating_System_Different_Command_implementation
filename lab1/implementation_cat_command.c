#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **str){
    for(int i = 1 ; i < argc ; i++){
        int fd = open(str[i], O_RDONLY) ;
        char buf[500] ;
        int n = read(fd,buf,sizeof(buf)) ;
        write(1,buf,n) ;
        printf("\n") ;
    }
    return 0 ;
}