#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

#define MEMLENGTH 512
static double memory[MEMLENGTH];

#define ROUNDUP8(x) (((x) + 7) & (-8))
int init = 0;


struct metadata{
        int size;
        int isFree; 
    }; 
 

void *mymalloc(size_t size, char *file, int line){

    // Can't allocate 0 or negative bytes
    if(size <= 0){
        printf("Can't allocate negative or 0 bytes of memory in %s on line %d.", file, line);
        exit(1);
    }

    // Can't allocate more than 4080 bytes, due to our design
    if(size >= MEMLENGTH * 8 - 16){
        printf("Can't allocate more memory than available in the memory pool in %s on line %d.", file, line);
        exit(1);
    }



   

    double *start = &memory[0]; //pointer to start of the heap
    double *end = &memory[0] + MEMLENGTH; //pointer to the heap of the heap
    struct metadata *first = (struct metadata *) start; //setting up metadata to be inserted at the first position of the heap
    size = ROUNDUP8(size); 
    size = size / 8; // Every position in the array corresponds to 8 bytes, so we set size to be how many indices the size will take up
    void* res = NULL; // pointer to be returned to user 
    struct metadata *currBlock;
     

    if(!init){ // First initialization of malloc
        init = 1;
        first->size = size;
        first->isFree = 1; // signifying block is not free anymore
        double *insert = (double *)first; 
        memory[0] = *insert; //inserting first metadata block in heap
        res = (start)+1; // moving pointer to point to the actual data

        struct metadata *last = (struct metadata *) &memory[MEMLENGTH - 1]; //inserting metadata at end
        last->size = 0;
        last->isFree = 1;
        double *end = (double*)last; 

        memory[MEMLENGTH - 1] = *end;

        start = (start + 1) + size; 
        struct metadata *second = (struct metadata *) start; // second metadata after first block to signify how much indices are left in the array
        second->size = MEMLENGTH - size - 2;
        second->isFree = 0; 
        double *toInsert = (double*) second;
        *(start) = *toInsert; //inserting second metadata 
        return res; 
    }

    else
    {
    while(start < end - 1){ // malloc has already been called, go from start to the position of the last metadata in the heap
        double *ptr = start; // pointer to the start of the array
        currBlock = (struct metadata*)ptr; // getting metadata at current position
        int chunkSize = currBlock->size; // getting size of metadata block
        int freedom = currBlock->isFree; // whether metadata block is free or not

         if(freedom == 1 || chunkSize < size){ // if not free, or incoming size is greater than the metadata's, skip to next position in heap
            start = (start + 1) + chunkSize;
        }

        else if(freedom == 0 && chunkSize >= size){ // metadata is free and can handle the incoming size
           
            int remainingSize = chunkSize - size - 1; // remaining indices in the heap
            currBlock->size = size;
            currBlock->isFree=1;
         
            res = start + 1; 

            if(*((start + 1) + size) == 0 || remainingSize - size != 0){ // cheecking if next position in heap is uninitialized, or size is less than remaining positions in the free section
                start =  (start + 1) + (size); // skip to that position
                struct metadata *dataAfter = (struct metadata *) start; // set up metadata block
                dataAfter-> size = remainingSize; // how many remaining positions are in the freed section of the heap
                dataAfter-> isFree = 0; // signify that it is free

                double *dataAfterValue = (double*) dataAfter;
                *(start) = *dataAfterValue; 

            }
          

            return res;
        }
     }

    printf("Error: not enough memory, calling from file %s on line %d. \n", file, line); // If function hits this, this means there was not enough free memory to allocate to user
    exit(1);
    }
}

void myfree(void *ptr, char *file, int line){
    double *start = &memory[0]; // pointer to start of heap
    double *end = memory + MEMLENGTH; // pointer to end of heap
    struct metadata *currBlock; 
    int notValidPtr = 1; // to keep track if the pointer provided by user is a valid pointer

    while(start < end-1){
        currBlock = (struct metadata*) start;
        int chunkSize = currBlock->size;
        if(chunkSize == 0){ // we know that the size of last metadata is 0, so if we reach this point, a valid pointer has not been reached
            break;
        }
        if(currBlock->isFree == 0){ // if block is free
            double *temp = (start + 1) + (chunkSize);
            struct metadata *jump = (struct metadata *) temp;
            if (jump -> isFree == 0 && jump -> size != 0){ // checking if adjacent block is free, and not the last metadata, if so, coalesce them
                currBlock->size = jump->size + chunkSize + 1;
                
            }
        }
        else if((start + 1) == ptr && currBlock->isFree == 1){ // if metadata block is the one being pointer to by ptr, and it is occupied
            notValidPtr = 0; // found valid pointer
            currBlock->isFree = 0; // set it to free
            double *temp = (start + 1) + (chunkSize);
            struct metadata *jump = (struct metadata *) temp;
            
             if (jump -> isFree == 0){ //checking if adjacent block is free, and not the last metadata, if so, coalesce them

                currBlock->size = jump->size + chunkSize+1;
            }
            
           
        }
        start = (start + 1) + currBlock->size; // using start to jump positions in the array for next iteration of loop
    }
    
    if(notValidPtr){ // pointer given by user has not been found in array
        printf("Not a valid pointer, calling from file %s on line %d\n.", file, line);
        exit(1);
    }


    // last check to coalesce any free blocks together that the previous loop could have missed
    double *start2 = &memory[0];
    struct metadata *currBlock2 = (struct metadata*) start2;
    int chunkSize2 = currBlock2->size;
    double *temp = (start2 + 1) + (chunkSize2);
    struct metadata *jump = (struct metadata *) temp; 

    if (jump -> isFree == 0 && jump -> size != 0 && currBlock2->isFree == 0){
        currBlock2->size = currBlock2->size + jump->size + 1;
    }


    return;
}

// function to see if heap was cleared altogether properly
int memCleared(){
    double *start = &memory[0];
    struct metadata *currBlock = (struct metadata*) start;
    int chunkSize = currBlock->size;
    int isFree = currBlock->isFree;
    
    // if everything coalesced together, first metadata block will have "size" 511 + 1 metadata block at end of array, totaling 512, size of array
    // or if heap was uninitialized in general, first element of memory will be 0
    if ((chunkSize == 511 && isFree == 0) || (memory[0] == 0) ){
        printf("Memory is successfully cleared!");
        return 1;
    }

    return 0;
}

