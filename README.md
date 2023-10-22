# mymalloc
CS 214 Project 1: Making a custom version of malloc() and free()  <br>
Names: Akash Shah and Teerth Patel  <br>
NetIDs: ass209 and tp554

Main idea <br>
The main purpose of this project is to emulate the functionality of the “malloc” and “free” functions <br>
found in the C standard library. These two functions serve crucial roles in helping a programmer allocate <br>
memory a multitude of different memory using program tools like pointers or arrays. Malloc itself takes <br>
any given amount of needed memory and allocates it for the user within the heap while free will free <br>
that memory when it is done being used. Our goal here is to make sure that we can do this just as well. <br>

Test Plans <br>
The main goal with our test plan was to push our malloc beyond what was seen throughout the first 3 <br>
tests mainly in the size requirements and in general intensity.<br>
Our first test is seen below: <br>
*this function is a void function. <br>
char* ptr1 = mymalloc(1, __FILE__, __LINE__);<br>
 char* ptr2 = mymalloc(100, __FILE__, __LINE__);<br>
 char* ptr3 = mymalloc(1000, __FILE__, __LINE__);<br>
 char* ptr4 = mymalloc(2000, __FILE__, __LINE__);<br>
 myfree(ptr1, __FILE__, __LINE__);<br>
 myfree(ptr2, __FILE__, __LINE__);<br>
 myfree(ptr3, __FILE__, __LINE__);<br>
 myfree(ptr4, __FILE__, __LINE__);<br>


 printf("MemClear?: %d\n", memCleared());<br>
Within this test we try our best to push malloc and see how it handles an increasing amount of data <br>
coming in as well as being able to properly free it all, the sizes range from a small single digit number to <br>
numbers within the thousands. The previous tests that were done all we similar in their size so that part <br>
of the program never got to do any work. Successfully running this test would tell us that our malloc can <br>
both allocate and free a multitude of different sizes even in situations where they are consecutively <br>
being put in, just like the real malloc. <br>
Our second test is seen below: <br>
 int p1 = mymalloc(8, FILE, LINE); <br>
 int p2 = mymalloc(16, FILE, LINE); <br>
 myfree(p1, FILE, LINE); <br>
 p1 = mymalloc(32, FILE, LINE); <br>
 int *p3 = mymalloc(64, FILE, LINE); <br>
 if(memCleared()) { <br>
 printf("Error: mem wrongly cleared\n"); <br>
 exit(1); <br>
 } <br>
 myfree(p1, FILE, LINE); <br>
 myfree(p2, FILE, LINE);<br>
 myfree(p3, FILE, LINE);<br>
 if(memCleared()){<br>
 printf("Memory successfully cleared!. \n");<br>
 }<br>
This was a test of reallocation to make sure that the return address of our malloc was able to give a<br>
accurate address and amount of memory for the user to use. As seen above our program makes 2<br>
pointers which are then allocated to 2 different amounts, the first pointer is then reallocated before<br>
being freed, followed by a third pointer to see if there would not be any kind of overlap. All three are<br>
then freed and memory is checked to see if everything went through properly. <br>
Overall Performance:<br>
The following is the performance values for each of the given tests along with the two tests that we<br>
created
*the following performance values are all in microseconds and were ran on iLab machines<br>
Test1<b
9 microseconds <br>
Test2
1215 microseconds<br>
Test3
361 microseconds<br>
Test4
3 microseconds<br>
Test5
2 microseconds<br>


