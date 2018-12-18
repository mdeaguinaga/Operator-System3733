#include <stdio.h>

int get_filesize(char *s);

int main(int argc, char *argv[]) {
     
    if (argc != 2) {
        fprintf(stderr,"Usage: %s filename\n", argv[0]);
        return 1; 
    }   

    fprintf(stderr,"Finding size of file %s:\n", argv[1]);
    fprintf(stderr,"get_filesize returned %d\n",get_filesize(argv[1]));
    return 0;
}
