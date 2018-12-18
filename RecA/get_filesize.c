#include <sys/stat.h>

int get_filesize(char *path) {
   struct stat statbuf;
    int size;

   if (stat(path, &statbuf) == -1)
      return -1;
   else
      size = statbuf.st_size;
      return size;
}
