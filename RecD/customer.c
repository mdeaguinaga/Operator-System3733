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
    int req_buf;
    
    if (argc != 2){
        printf("Usage: %s fifoname \n", argv[0]);
        return 1;
    }

    // open pipe ro wright 
    if((req = open(argv[1], O_WRONLY)) == -1){
        printf("Client faild to open log fifo for writing");    
        return 1;
    }

    //loop for user
    while(1){
        printf("Enter an integer to deposit ");
        scanf("%d",&req_buf);

        if(req_buf < 0)
            break;

        //write the given integer into the pipe
        if(write(req, &req_buf, sizeof(req_buf)) != sizeof(req_buf)){
            printf("Clien failed to write");
            return 1;
        }

    }
    close(req);
    return 0;
}
