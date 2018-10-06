#include"regexGin.h"
// Don't forget the print function needs to be modified to print all of a state's transitions arrows on one line

void main(){

 struct stack_node* sentinel = stack_init();
 build_nfa(sentinel); 
 struct nFA* finished_nfa = pop(sentinel);
 print_transitions_one_line(finished_nfa);
 free_stack(sentinel);
 free_nfa(finished_nfa);
}


