#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

/********************************* main ***********************************
The program will take only one parameter, the name of address sequence file
, which contains a sequence of logical memory addresses accessed by the process. 
It save each logical/physical address as 64 bits (8 bytes) to make the program 
to be more general. That is, each logical addresses is saved as 8 bytes 
(unisgned long) in the address sequence file. It read and analyze each logical 
address, and translate it into the corresponding physical addresses based 
on the given page table as shown in the above picture. 
*************************************************************************/

int main(int argc, char *argv[]) {
   int addrtrans[] = {2, 4, 1, 7, 3, 5, 6};
   int fdin, fdout;
   unsigned long offset, page, physaddr, virtaddr;
   
   // checks for the input information from terminal
   if (argc != 2) {
       printf("Usage: %s Sequece File\n", argv[0]);
       exit(1);
   }
   
   // open on real only the information that is in argv[1]
   if ((fdin = open(argv[1], O_RDONLY)) == -1) {
       perror("Unable to open sequence file");
       exit(2);
   }
   
   // If the information that is inputed can't be readed, it prints an error
   if ((fdout = open("output-part1", O_WRONLY | O_CREAT, 0600)) == -1) {
       perror("Unable to open output file");
       close(fdin);
       exit(2);
   }
   
   // While loop that reads and assign the information
   while (read(fdin, &virtaddr, sizeof(virtaddr)) > 0) {
      offset = virtaddr & 0x7F;
      page = virtaddr >> 7;
      page = addrtrans[page];
      physaddr = page << 7;
      physaddr += offset;

      // Checks for possible errore while writing 
      if (write(fdout, &physaddr, sizeof(physaddr)) == -1) {
          perror("Failed to write to output file");
          exit(3);
      }
   }
   
   close(fdin);
   close(fdout);
   
   return 0;
}
