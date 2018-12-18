#include<errno.h>
#include<string.h>
#include<sys/select.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdio.h>
#include<fcntl.h>

#define FIFO_PERMS (S_IRWXU | S_IWGRP | S_IWOTH)

int whichisready(int fd1, int fd2);

int main(int argc, char *argv[]){
    char *ATM1 = "ATM1";
    char *ATM2 = "ATM2";
    int fd, fd1, fd2;
    int TOTAL;
    
    if((mkfifo(ATM1, FIFO_PERMS) == -1) && (errno != EEXIST)){
        printf("server failed to create a FIFO");
        return 1;
    }
    if((mkfifo(ATM2, FIFO_PERMS) == -1) && (errno != EEXIST)){
        printf("server failed to create a FIFO");
        return 1;
    }
    if((fd1 = open(ATM1, O_RDWR)) == -1){
        printf("server failed to open its FIFO");
        return 1;
    }
    if((fd2 = open(ATM2, O_RDWR)) == -1){
        printf("server failed to open its FIFO");
        return 1;
    }
    while(1){
        // Calls wich pipe is ready
        fd = whichisready(fd1 , fd2);
        // assign info to TOTAL
        read(fd, &TOTAL ,sizeof(int));
        printf("%d\n",TOTAL);
    }
    return 1;
}

int whichisready(int fd1, int fd2){
    int maxfd;
    int nfds;       
    fd_set readset;

    maxfd = (fd1 > fd2) ? fd1 : fd2;
    FD_ZERO(&readset);
    FD_SET(fd1, &readset);
    FD_SET(fd2, &readset);
    nfds = select(maxfd+1, &readset, NULL, NULL, NULL);
    
    if (nfds == -1)
        return -1;
    if (FD_ISSET(fd1, &readset))
        return fd1;
    if (FD_ISSET(fd2, &readset))
        return fd2;
    errno = EINVAL;
    return -1;
}
