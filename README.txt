Author: Ryan Paulos

Project: This tar file contains all .c files to construct a program that constructs an NFA from a given postfix regular expression
and outputs the transition functions of the NFA.  The program reads from stdin, so redirect the contents of the test file as such.
No further action by the user is necessary. The program will print the transition functions of the constructed NFA or, if applicable, will produce a relevant error message and terminate.


Building: This archive includes a Makefile to simplify the construction of the program. Simply type 'make'.


Files:
 main.c: Primary controller of the program. Consists of only a few lines which call the program's subroutines.  

 core.c: Contains the majority of the program and the core set of logic responsible for parsing the regular expression.

 nfaBuilder.c: Contains the functions the construct NFAs from single alphabet components and the operator logic.

 stack.c: The functions necessary to manipulate the stack onto which the pieces of the in-progress NFA are pushed.

 ancillary.c: Contains the printing and free-ing helper functions.
