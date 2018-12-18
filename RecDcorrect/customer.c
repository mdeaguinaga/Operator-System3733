#include <errno.h> 
#include <unistd.h>
#include <sys/select.h>
#include <stdio.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
int main(int argc, char *argv[]){
    int req;
    int len;
    char req_buf[10];
    int i;
    if (argc != 2){
        printf("Usage: %s fifoname \n", argv[0]);
        return 1;
    }

/*    if ((mkfifo(argv[1], FIFO_PERMS) == -1) &&(errno != EEXIST)) {

    }*/

    if((req = open(argv[1], O_WRONLY)) == -1){
        printf("Client faild to open log fifo for writing");    
        return 1;
    }
    while(1){
        printf("Enter an integer to deposit");
        scanf("%s",req_buf);

        len = strlen(req_buf);
        i = atoi(req_buf);

        if(i < 0)
            break;
        if(r_write(req, req_buf, len) != len){
            printf("Clien failed to write");
            return 1;
        }

    }
    close(req);
    return 0;
}
