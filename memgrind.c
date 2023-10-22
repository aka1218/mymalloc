    #include "mymalloc.c"
    #include <time.h> 

    void test1() {
        printf("Entered test.");
        for(int i = 0; i < 120; i++) {
            char *ptr = mymalloc(1, __FILE__, __LINE__);  // Allocate 1 byte of memory
            myfree(ptr, __FILE__, __LINE__);  // Release the memory
        }
        
        printf("MemClear?: %d\n", memCleared()); // Check if memory is cleared
    }

    void test2() {
        char *ptrArray[120];  // Array to store 120 pointers
        for(int i = 0; i < 120; i++) {
            ptrArray[i] = mymalloc(1, __FILE__, __LINE__); 
            printf("%d\n", i); // Allocate 1 byte of memory and store the address
                
            }
            for(int i = 0; i < 120; i++) {
                myfree(ptrArray[i], __FILE__, __LINE__);
                printf("%d\n", i);   // Release the memory
            }
            printf("MemClear?: %d\n", memCleared());;
    }
    


    void test3() {
        char *ptrArray[120];  // Array to store 120 pointers
        int allocated[120] = {0};  // Initialize the memory allocation status array
        int loc = 0;  // Current location
        
        for(int i = 0; i < 120; i++) {
            if(loc == 0 || (rand() % 2 == 0 && loc < 120)) {
                // Allocate 1 byte of memory and store the address
                printf("alloc loc=%d\n", loc);
                ptrArray[loc] = mymalloc(1, __FILE__, __LINE__);
                allocated[loc] = 1;
                loc++;
            } else {
                // Release the memory
                loc--;
                printf("free loc=%d\n", loc);
                myfree(ptrArray[loc], __FILE__, __LINE__);
                allocated[loc] = 0;
            }
        }
    

        printf("Process is done.\n");

        // Clean up any unreleased memory
        for(int i = 0; i < 120; i++) {
            if(allocated[i] == 1) {
                myfree(ptrArray[i], __FILE__, __LINE__);
                }
            }
         
        printf("MemClear?: %d\n", memCleared());  // Check if memory is cleared

    }

    void test4(){

        
        char* ptr1 = mymalloc(1, __FILE__, __LINE__);
        char* ptr2 = mymalloc(100, __FILE__, __LINE__);
        char* ptr3 = mymalloc(1000, __FILE__, __LINE__);
        char* ptr4 = mymalloc(2000, __FILE__, __LINE__);


        myfree(ptr1, __FILE__, __LINE__);
        myfree(ptr2, __FILE__, __LINE__); 
        myfree(ptr3, __FILE__, __LINE__);
        myfree(ptr4, __FILE__, __LINE__);
        
        
        printf("MemClear?: %d\n", memCleared());

    }

    void test5(){
        
       // Test basic allocation
    int *p1 = mymalloc(8, __FILE__, __LINE__);
    int *p2 = mymalloc(16, __FILE__, __LINE__);
    
    // Test freeing 
    myfree(p1, __FILE__, __LINE__);

    // Test reallocation
    p1 = mymalloc(32, __FILE__, __LINE__);

    // Test allocation after free
    int *p3 = mymalloc(64, __FILE__, __LINE__);

    // Check mem not cleared on second run
    if(memCleared()) {
        printf("Error: mem wrongly cleared\n");
        exit(1);
    }

    // Free all 
    myfree(p1, __FILE__, __LINE__);
    myfree(p2, __FILE__, __LINE__);
    myfree(p3, __FILE__, __LINE__);

    if(memCleared()){
        printf("Memory successfully cleared!. \n");
    }

    
    }


     

    int main(){
        struct timeval tv_start, tv_end;
        printf("Starting.");

        gettimeofday(&tv_start, NULL);
        for(int j = 0; j < 50; j++){
            test1();
        }
        gettimeofday(&tv_end, NULL);
        printf("Average number of microseconds for each iteration of test 1: %ld \n", ((tv_end.tv_usec - tv_start.tv_usec)/50));

        // gettimeofday(&tv_start, NULL);
        // for(int j = 0; j < 50; j++){
        //     test2();
        // }

        // gettimeofday(&tv_end, NULL);
        // printf("Average number of microseconds for each iteration of test 2: %ld\n", ((tv_end.tv_usec - tv_start.tv_usec)/50));

        // gettimeofday(&tv_start, NULL);
        // for(int j = 0; j < 50; j++){
        //     test3();
        // }

        // gettimeofday(&tv_end, NULL);
        // printf("Average number of microseconds for each iteration of test 3: %ld \n", ((tv_end.tv_usec - tv_start.tv_usec)/50));

        // gettimeofday(&tv_start, NULL);
        // for(int j = 0; j < 50; j++){
        //     test4();
        // }
        // gettimeofday(&tv_end, NULL);
        // printf("Average number of microseconds for each iteration of test 4: %ld \n", ((tv_end.tv_usec - tv_start.tv_usec)/50));
        

        // gettimeofday(&tv_start, NULL);
        // for(int j = 0; j < 50; j++){
        //     test5();
        // }
        // gettimeofday(&tv_end, NULL);
        // printf("Average number of microseconds for each iteration of test 5: %ld \n", ((tv_end.tv_usec - tv_start.tv_usec)/50));

    }