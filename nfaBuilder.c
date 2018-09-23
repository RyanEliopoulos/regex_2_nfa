#include"regexGin.h"

int counter = 0; // Tracks next available state identifier



// Builds an NFA containing a single symbol and two states.
struct nFA* build_nfa_from_char(int symbol){

  struct nFA* tempFA = malloc(sizeof(struct nFA));

  // Assign unique integer identifiers to the states
  int origin = counter++;
  int destination = counter++;
  tempFA->start_state = origin;
  tempFA->final_state = destination;

  struct transition_node* tempL = list_init(origin, destination, symbol);

  tempFA->trans_list = tempL;
 
  return tempFA; 
}


void modify_nfa_union(struct nFA* NFA1, struct nFA* NFA2){

  int new_start_state = counter++;
  int new_final_state = counter++;

  // E slide from NFA1 to the accept state of the new UNIONed NFA 
  struct transition_node* temp = malloc(sizeof(struct transition_node));
  temp->origin_state = NFA1->final_state;
  temp->destination_state = new_final_state;
  temp->symbol = 6;
  temp->next_transition = NULL;
  join_transition_list(NFA1->trans_list, temp);
  
  // E slide from NFA2 to the accept state of the new UNIONed NFA
  struct transition_node* temp2 = malloc(sizeof(struct transition_node));
  temp2->origin_state = NFA2->final_state;
  temp2->destination_state = new_final_state;
  temp2->symbol = 6;
  temp2->next_transition = NULL;
  join_transition_list(NFA2->trans_list, temp2);

  
  // Combining NFA1 and NFA2 transition lists (order preserved)
  join_transition_list(NFA1->trans_list, NFA2->trans_list);    

  // Constructing the E slides from the new start state to the former start states 
  // to NFA1
  struct transition_node* new_transition1 = malloc(sizeof(struct transition_node));
  new_transition1->origin_state = new_start_state;
  new_transition1->destination_state = NFA1->start_state;
  new_transition1->symbol = 6;
  new_transition1->next_transition = NULL; 
  join_transition_list(NFA1->trans_list, new_transition1);

  // to NFA2
  struct transition_node* new_transition2 = malloc(sizeof(struct transition_node));
  new_transition2->origin_state = new_start_state;
  new_transition2->destination_state = NFA2->start_state;
  new_transition2->symbol = 6;
  new_transition2->next_transition = NULL; 
  join_transition_list(NFA1->trans_list, new_transition2);

  NFA1->start_state = new_start_state;  
  NFA1->final_state = new_final_state;

  free(NFA2);
}





// Cats NFA2 onto NFA1 following standard automata protocol
void modify_nfa_concatenation(struct nFA* NFA1, struct nFA* NFA2){

  // Add E slide that combines the two NFAs
  struct transition_node* temp = malloc(sizeof(struct transition_node));
  temp->origin_state = NFA1->final_state;
  temp->destination_state = NFA2->start_state;
  temp->symbol = 6;
  temp->next_transition = NULL;   
  
  // Appending the new transition
  struct transition_node* list_end = NFA1->trans_list;
  while(list_end->next_transition != NULL){
    list_end = list_end->next_transition;
  } 
  list_end->next_transition = temp; 

  // Append NFA2's transitions to NFA1
  join_transition_list(NFA1->trans_list, NFA2->trans_list); 
  
  // Update the new accept state
  NFA1->final_state = NFA2->final_state;

  free(NFA2);

}






/* Modifies the given NFA by creating a new state, which becomes both the accept state and the start state. This new state
 * E slides to the former start state, and the former accept state E slides into the new state
 */
void modify_nfa_kleene_star(struct nFA* target_nfa){

  int new_state = counter++;
  
  // Create transition from the new state 
  struct transition_node* new_state_trans = malloc(sizeof(struct transition_node*));
  new_state_trans->origin_state = new_state;
  new_state_trans->destination_state = target_nfa->start_state;
  new_state_trans->symbol = 6;
  new_state_trans->next_transition = NULL; 

  // Create transition from old accept state to new state
  struct transition_node* to_new = malloc(sizeof(struct transition_node));
  to_new->origin_state = target_nfa->final_state;
  to_new->destination_state = new_state;
  to_new->symbol = 6;
  to_new->next_transition = new_state_trans;

  join_transition_list(target_nfa->trans_list, to_new); // append latest transitions

  // update NFA's start and accept states
  target_nfa->start_state = new_state;
  target_nfa->final_state = new_state;
}


// Still need to test this against larger NFAs. So far it works with kleene star
void join_transition_list(struct transition_node* older_list, struct transition_node* latest_list){

  // Finding last transition
  struct transition_node* temp = older_list;
  while(temp->next_transition != NULL){
    temp = temp->next_transition;
  }

  temp->next_transition = latest_list;
}


// Inits transition list for an NFA containing a single symbol and two states.
struct transition_node* list_init(int origin, int destination, int symbol){

  struct transition_node* temp = malloc(sizeof(struct transition_node));
  temp->origin_state = origin;
  temp->destination_state = destination;
  temp->symbol = symbol;
  temp->next_transition = NULL;
}




