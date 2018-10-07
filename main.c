/*
 * Ryan Paulos
 * CS 317
 * 10/6/2018
 *
 *
 * This program readis from stdin a series of characters representing the alphabet of a finate automaton (a,b,c,d,e) and 
 * the characters representing regular expression operations (concatenation: &, kleene star: *, union: |), creating a 
 * corresponding NFA.
 *
 * Parsing and error checking exists to make sure the expression is complete. The NFA is constructed piecemeal using a stack
 * which builds smaller NFAs into larger ones until only one remains on the stack.
 *
 * The program prints the transition functions for each node in the NFA before terminating.
 */



#include"regexGin.h"

// As it says
void main(){

 struct stack_node* sentinel = stack_init(); // Stack handle
 build_nfa(sentinel);  // Majority of the program

 // Printing
 struct nFA* finished_nfa = pop(sentinel);
 print_transitions_one_line(finished_nfa);

 // Clean up
 free_stack(sentinel);
 free_nfa(finished_nfa);
}


