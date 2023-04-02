# Garbage Collection
C for Garbage Colleciton

Jiyong Kwag

Submitting files:

1. core.h: containing the core keyword, symbols and others of the language
2. executor.c: contains the executable C file that execute the parseTree into executable program.
3. executor.h: cotains the header files for executro.c
4. main.c: run the whole program
5. memory.c: cotains the data structure of the program. It handles the variable names and their values into array of integer variables and record array. Moreover, it counts the new object that is created and decrement the object count when no record is pointing to the object.
6. memory.h: header file for memory.c
7. parser.c: Recieving the file name from the main and processing the parsing with scanner
8. parser.h: header file for parser.c
9. scanner.c: Recieving the file name from the main and processing the tokenizing the program
10. scanner.h: header file for parser.c
11. tree.h: testing the parser
12. Readme.Md

Any Special Feature:

In the project, I created the function that count number of objects during program run. Furthremore, whenever the scope of function is finished, only objects that is created in the scope is eliminated.

Decription:

In the project5, we are asked to implement garbage collection on the executing program. In the program, there are several scopes that the garbage collection is working: when main body, method, or while scope is doen. When each of the scope is finished, the object that is initialized in that scope should be garbage collected by program for the memory purpose. So, in this projection, I implemented the garabage collection and its verifying methods.

Testing:

I tired with several scopes and objects in the each of the scope that I mentioned in description. Then, I changed back and forth between scopes to see if the garbage collection is correctly recognize the current scope is done to initiate the garabage collect the object in the scope.