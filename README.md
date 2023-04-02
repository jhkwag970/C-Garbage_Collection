# Function_Call
C for Function Call

Jiyong Kwag

Submitting files:

1. core.h: containing the core keyword, symbols and others of the language
2. executor.c: contains the executable C file that execute the parseTree into executable program.
3. executor.h: cotains the header files for executro.c
4. main.c: run the whole program
5. memory.c: cotains the data structure of the program. It handles the variable names and their values into array of integer variables and record array.
6. memory.h: header file for memory.c
7. parser.c: Recieving the file name from the main and processing the parsing with scanner
8. parser.h: header file for parser.c
9. scanner.c: Recieving the file name from the main and processing the tokenizing the program
10. scanner.h: header file for parser.c
11. tree.h: testing the parser
12. Readme.Md

Any Special Feature:

In the project, I made the struct array of the function that manages all of the functions in the program. Thus, we do not have to parse down the tree everytime the main program calls the functions, which reduce the runtime significantly. 

Decription:

In the project4, we are asked to implement further on function calling, which include the recursion. We are given the language that contains the func-seq, function, paramter, and call non terminal that can declare and execute the functions in the program. In the main method, user can call the function that is declared and execute the stmt seq of the function that can call itselft, in other word recursion. Then, we also implemented the some semantic and parse checks of the function: error on duplicate method, unmatched number of paramter. 

Testing:

I tried several test case of function: whether the argument and formal paramters are matched well to be used in the function call. Then, I tested the recursion of the function. 
