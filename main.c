#include"regexGin.h"
// Don't forget the print function needs to be modified to print all of a state's transitions arrows on one line

void main(){

 struct stack_node* sentinel = stack_init();
 build_nfa(sentinel); 

 struct nFA* finished_nfa = pop(sentinel)->nfa;

 print_transitions_one_line(finished_nfa);
}


void print_transitions_one_line(struct nFA* NFA){

  struct transition_node* temp = NFA->trans_list;
  int state_marker = -1; //Helps print all transitions on one line
  int latest_node_with_exit_arrows = -1; // Used to determine if manual printing of the accept state is necessary
  

  // Loops through transitions
  while(temp != NULL){
    
    // Used to determine if the last state has any exit arrows 
    if(temp->origin_state > latest_node_with_exit_arrows){
      latest_node_with_exit_arrows = temp->origin_state;
    } 

    // Since the list of transitions is in ascending order, a new state marker means a the transitions are now for a 
    // new state, requiring a new line.
    if(state_marker != temp->origin_state){
      state_marker = temp->origin_state;
      printf("\n");  

      if(temp->origin_state == NFA->final_state && temp->origin_state == NFA->start_state){
        printf("S,F(q%d,%c)-> q%d", temp->origin_state, temp->symbol, temp->destination_state);
      }
      else if(temp->origin_state == NFA->start_state){
        printf("S(q%d,%c)-> q%d", temp->origin_state, temp->symbol, temp->destination_state);
      }
      else if(temp->origin_state == NFA->final_state){
        printf("F(q%d,%c)-> q%d", temp->origin_state, temp->symbol, temp->destination_state);
      }
      else{
        printf("(q%d,%c)-> q%d", temp->origin_state, temp->symbol, temp->destination_state);
      }
    } 
    else{
      printf(",%d", temp->destination_state);
    }
    temp = temp->next_transition;
  }

  // Executes when the final state has no exit arrows
  if(NFA->final_state > latest_node_with_exit_arrows){
    printf("\nF(q%d,E)->", NFA->final_state);
  }
  printf("\n");
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
