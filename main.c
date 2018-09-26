#include"regexGin.h"
// Don't forget the print function needs to be modified to print all of a state's transitions arrows on one line

void main(){

 struct stack_node* sentinel = stack_init();
 build_nfa(sentinel); 

 struct nFA* finished_nfa = pop(sentinel)->nfa;

 print_transitions(finished_nfa);
}


// Cycles through the transition list in ascending order, printing them as it goes.
void print_transitions(struct nFA* NFA){
  
  struct transition_node* temp = NFA->trans_list;
  int latest_node_with_exit_arrows = 0; // Used to determine if manual printing of the accept state is necessary

  while(temp != NULL){

    // This helps solve the problem of listing a final state that has no exit arrows
    if(temp->origin_state > latest_node_with_exit_arrows){ 
      latest_node_with_exit_arrows = temp->origin_state;
    }

    if(temp->origin_state == NFA->final_state && temp->origin_state == NFA->start_state){
      printf("S,F(q%d,%c)-> q%d\n", temp->origin_state, temp->symbol, temp->destination_state);
    }
    else if(temp->origin_state == NFA->start_state){
      printf("S(q%d,%c)-> q%d\n", temp->origin_state, temp->symbol, temp->destination_state);
    }
    else if(temp->origin_state == NFA->final_state){
      printf("F(q%d,%c)-> q%d\n", temp->origin_state, temp->symbol, temp->destination_state);
    }
   else{
      printf("(q%d,%c)-> q%d\n", temp->origin_state, temp->symbol, temp->destination_state);
    }

    temp = temp->next_transition;
  }
  
  if(NFA->final_state > latest_node_with_exit_arrows){
    printf("F(q%d,E)->\n", NFA->final_state);
  }

}
