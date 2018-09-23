#include"regexGin.h"


void main(){

  struct nFA* test = build_nfa_from_char(1);
  modify_nfa_kleene_star(test);

  struct nFA* test2 = build_nfa_from_char(4);
  modify_nfa_concatenation(test, test2);

  modify_nfa_kleene_star(test);
  printf("\n\n\nUnion\n\n\n");

  // gonna try union now
  struct nFA* test3 = build_nfa_from_char(3);
  modify_nfa_union(test, test3);
  print_transitions(test);
}


// Cycles through the transition list in ascending order, printing them as it goes.
void print_transitions(struct nFA* NFA){
  
  struct transition_node* temp = NFA->trans_list;
  int latest_node_with_exit_arrows = 0; // Used to determine if manual printing of the accept state is necessary

  while(temp != NULL){
    if(temp->origin_state > latest_node_with_exit_arrows){
      latest_node_with_exit_arrows = temp->origin_state;
    }

    if(temp->origin_state == NFA->final_state && temp->origin_state == NFA->start_state){
      printf("S,F(q%d,%d)-> q%d\n", temp->origin_state, temp->symbol, temp->destination_state);
    }
    else if(temp->origin_state == NFA->start_state){
      printf("S(q%d,%d)-> q%d\n", temp->origin_state, temp->symbol, temp->destination_state);
    }
    else if(temp->origin_state == NFA->final_state){
      printf("F(q%d,%d)-> q%d\n", temp->origin_state, temp->symbol, temp->destination_state);
    }
   else{
      printf("(q%d,%d)-> q%d\n", temp->origin_state, temp->symbol, temp->destination_state);
    }

    temp = temp->next_transition;
  }
  
  if(NFA->final_state > latest_node_with_exit_arrows){
    printf("F(q%d,E)->\n", NFA->final_state);
  }

}
