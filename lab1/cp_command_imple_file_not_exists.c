#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **str){
    int fd1 = open(str[1],O_RDONLY) ;
    char buf[500] ;
    int n = read(fd1,buf,sizeof(buf)) ;
    open(str[2],O_CREAT) ;
    int fd2 = open(str[2],O_WRONLY) ;
    write(fd2,buf,n) ;
    return 0 ;
}