/*
 * Ryan Paulos
 *
 *
 */


#include<stdlib.h>
#include"regexGin.h"

// Returns NULL if the stack is empty. Otherwise returns the NFA off the top
struct nFA* pop(struct stack_node* sentinel){

  if(sentinel->next == NULL){ // Stack is empty
    return NULL;
  }
  
  // Modifies stack and retrieves nfa
	struct stack_node* popped_node =	sentinel->next;	
	sentinel->next = popped_node->next; // Removes popped node from the chain
  struct nFA* popped_nfa = popped_node->nfa;
  free(popped_node);

  return popped_nfa;
}


// Sentinel points to the top of the stack. 
//  - Terminates program if malloc fails
//  - returns 1 upon success
int push(struct stack_node* sentinel, struct nFA* pushed_nfa){

	struct stack_node* temp = malloc(sizeof(struct stack_node));

	// Returns 0 when malloc fails to allocate requested memory
	if(temp == NULL){
    printf("System has run out of memory..terminating\n");
    free_stack(sentinel);
    exit(4);
	}

	// Inserts the new link into the chain
	temp->nfa = pushed_nfa;
	temp->next = sentinel->next;
	sentinel->next = temp;	

	return 1;
}


// Creates the sentinel node for a stack. Sentinel comes with an NFA to faciltate the free_stack function
struct stack_node* stack_init(){

	struct stack_node* sentinel = malloc(sizeof(struct stack_node));

  if(sentinel == NULL){
    printf("Insufficient memory to execute program..terminating\n");
    exit(4);
  }

  // For debugging/referencing
  struct nFA* temp = malloc(sizeof(struct nFA));
  temp->start_state = -9999;
  temp->final_state = -9999;
  int origin = -9999;
  int destination = -9999;
  char symbol = 'E';
  
  // Necessary for free-ing functions
  struct transition_node* tempL = list_init(origin, destination, symbol);
  temp->trans_list = tempL;

	sentinel->nfa = temp;
	sentinel->next = NULL;

	return sentinel;
}


// Frees all allocated memory from the program. Traverses the stack, freeing stack nodes and their 'children' structs 
void free_stack(struct stack_node* sentinel){

  // To traverse the stack
  struct stack_node* current_node = sentinel;
  struct stack_node* next_node = sentinel->next;

  // Traversing the stack and free the node's NFAs
  while(next_node != NULL){
    free_nfa(current_node->nfa);
    free(current_node);
    current_node = next_node;
    next_node = next_node->next;
  }

  free_nfa(current_node->nfa);
  free(current_node);
}



