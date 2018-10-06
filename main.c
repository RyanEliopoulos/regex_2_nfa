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


