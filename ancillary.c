/*
 * Ryan Paulos
 *
 *
 */

#include"regexGin.h"


// Frees the list of transitions associated with the passed nfa, then frees the nfa itself
void free_nfa(struct nFA* nfa){

  struct transition_node* current_transition = nfa->trans_list;
  struct transition_node* next_transition = current_transition->next_transition;
 
  // traverses the transition list, freeing nodes as it advances 
  while(next_transition != NULL){
    free(current_transition);
    current_transition = next_transition;
    next_transition = next_transition->next_transition; 
  }
  
  free(current_transition);
  free(nfa);
}


// Responsible for printing the transition functions
// Annoyingly long name because the old print_transitions function didn't (one_line).
void print_transitions_one_line(struct nFA* NFA){

  struct transition_node* temp = NFA->trans_list;
  int state_marker = -1; //Helps print all transitions on one line
  int latest_node_with_exit_arrows = -1; // Used to determine if manual printing of the accept state is necessary
  
  // Loops through transitions
  while(temp != NULL){
    
    // Used to determine if the last state has any exit arrows. Requires compensation if not
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


