#include<stdlib.h>
#include"regexGin.h"

// Returns NULL if the stack is empty. Otherwise returns the NFA off the top
struct stack_node* pop(struct stack_node* sentinel){

  if(sentinel->next == NULL){ // Stack is empty
    return NULL;
  }

	struct stack_node* popped_node =	sentinel->next;	

	sentinel->next = popped_node->next; // Removes popped node from the chain
  return popped_node;

}

// Adds given number to the stack. Returns 1 if successful and 0 if malloc fails (out of memory)
// New nodes are inserted at the front of the list, pointed to by the sentinel, and point to the node direct beneath them in the stack.
// Fnx takes pointer to the stack sentinel and the number to be inserted.
int push(struct stack_node* sentinel, struct nFA* pushed_nfa){

	struct stack_node* temp = malloc(sizeof(struct stack_node));

	// Returns 0 when malloc fails to allocate requested memory
	if(temp == NULL){
		return 0;
	}

	// Inserts the new link into the chain
	temp->nfa = pushed_nfa;
	temp->next = sentinel->next;
	sentinel->next = temp;	

	return 1;
}

// Iterates through the given list and frees each node as it goes
//void releaseStack(struct stackNode* sentinel){
//
//	// Placeholders used for list traversal
//	struct stackNode *previousNode = sentinel;
//	struct stackNode *currentNode = sentinel->next;
//
//	// Iterates through the list releasing each node as it goes, releasing n-1 nodes
//	while(currentNode != NULL){
//		free(previousNode);
//		previousNode = currentNode;
//		currentNode = currentNode->next;
//	
//	
//	}
//	// Releases final node	
//	free(previousNode);
//
//}
//
//// Traverses the given list, printing each node value as it goes
//void print_stack(struct stackNode* sentinel){
//
//	struct stackNode* currentNode = sentinel->next;
//
//	// Detects empty stack
//	if(currentNode == NULL){
//		printf("TOS->\n");
//		return;
//	}
//
//	printf("TOS->");
//	
//	// Iterates through the stack up to n-1 and prints the data values
//	while(currentNode->next !=  NULL){
//		printf("%d, ", currentNode->data);
//		currentNode = currentNode->next;	
//	}				
//
//	printf("%d\n", currentNode->data); // Prints last node. Separate to preserve proper comma usage
//}



// Creates the sentinel node for a stack. Returns struct stackNode pointer.
struct stack_node* stackInit(){

	struct stack_node* sentinel = malloc(sizeof(struct stack_node));

  // For debugging/referencing
  struct nFA* temp = malloc(sizeof(struct nFA));
  temp->start_state = -9999;
  temp->final_state = -9999;

	sentinel->nfa = temp;
	sentinel->next = NULL;

	return sentinel;

}
