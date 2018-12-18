#include <stdlib.h>
#include "phypages.h"

/********************* initializeFrames ********************
int* initializeFrames(int** frames, int size)
parameters: 
        int ** frames, double pointer that holds the frames
        int size, size of frame 
 initializeFrames creates a memory space to input the information
 and hold the value in an frame array in order to check the 
 information that holds the the frame.
***********************************************************/
int* initializeFrames(int** frames, int size) { 
      int i;
      *frames = (int *)malloc(size * sizeof(int));  //Memori allocation
      (*frames)[0] = OS;

      // forloop that creates the frame and it size 
      for (i = 1; i < size; i++) {
         (*frames)[i] = NONE;
      }
      return *frames;
}

/******************** findOpen  **************************
int findOpen(int** frames, int size)
**********************************************************/
int findOpen(int** frames, int size) {
    int i;
    int frame = -1;
    for (i = 1; i < size; i++) {
        if ((*frames)[i] == -1) {
            frame = i;
            break;
        }
    }  
    return frame;
}

/******************** reverseMap ****************************
int* reverseMap(int** frames, int frame, int page) 
************************************************************/
int* reverseMap(int** frames, int frame, int page) {
      (*frames)[frame] = page;
      
      return *frames;
}
