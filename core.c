/*
 * Ryan Paulos
 *
 *
 */

#include"regexGin.h"

// Core logic of the program. Parses chars from stdin and manipulates stack/NFA calls as required.
// - Ignores whitespace characters
// - Terminates program if a character not specified as a member of the alphabet or operators is passed
// - Provides character # of invalid character (if one is detected)
void build_nfa(struct stack_node* sentinel){
  
  char c = fgetc(stdin);
  int input_char_count = 0; // For malformed input data referencing

  while(c != EOF){
    
    // Note: USE SWITCH NEXT TIME

    // Kleene Star
    if(c == '*'){
      if(input_char_count == 0){
        zero_index_operator();  
      }

      struct nFA* nfa = pop(sentinel);
      modify_nfa_kleene_star(nfa);
      push(sentinel, nfa);
    } 

    // Concatenation
    else if(c == '&'){
      if(input_char_count == 0){
        zero_index_operator();
      }   
      // Pop from stack
      struct nFA* nfa2 = pop(sentinel);
      struct nFA* nfa1 = pop(sentinel);
      
      // Terminates program if popping from an empty stack
      if(!empty_stack_check(input_char_count, nfa1, nfa2)){
        free_stack(sentinel);
        exit(7);
      }

      // Perform Operation 
      modify_nfa_concatenation(nfa1, nfa2);
      
      // Push new NFA
      push(sentinel, nfa1);
    } 

    // Union
    else if(c == '|'){
      if(input_char_count == 0){
        zero_index_operator();
      }

      // pop from stack
      struct nFA* nfa2 = pop(sentinel);
      struct nFA* nfa1 = pop(sentinel);

      // Terminates if popping from empty stack
      if(!empty_stack_check(input_char_count, nfa1, nfa2)){
        free_stack(sentinel);
        exit(7);
      }

      // perform operation
      modify_nfa_union(nfa1, nfa2);

      // push new nfa
      push(sentinel, nfa1);
    } 

    // Building a new nfa
    else if(c == 'a' || c == 'b' || c == 'c' || c == 'd' || c == 'e'){
      struct nFA* new_nfa = build_nfa_from_char(c);
      push(sentinel, new_nfa); 
    }
    
    // Whitespace is ignored
    else if(isspace(c)){
      // Negate the tick that occurs later
      input_char_count--;
    }

    // Invalid character detection
    else{
      printf("invalid character located at position %d\nTerminating\n", input_char_count);
      free_stack(sentinel);
      exit(5);
    }

    c = fgetc(stdin);
    input_char_count++;
  }
  ending_stack_check(sentinel);
}

// checks if there is more than one NFA left on the stack. If so, the input was wrong (cuz it can't be me!!)
void ending_stack_check(struct stack_node* sentinel){

  int node_count = 0;
  struct stack_node* temp = sentinel->next;
  while(temp != NULL){
    node_count++;
    temp = temp->next;
  }

  if(node_count > 1){
    printf("Multiple NFAs left on stack at EOF - Incomplete RE given\nTerminating\n");
    free_stack(sentinel);
    exit(3);
  }
  if(node_count < 1){
    printf("Ending stack count is less than 1. Panic\n");
  }
}


// Detects popping from an empty stack, which is really just malformed input data
int empty_stack_check(int input_char_number, struct nFA* last_nfa, struct nFA* almost_last_nfa){
  if(last_nfa == NULL){
    printf("Popping from empty stack at input character %d\n", input_char_number+1);
    printf("Terminating\n");
    free_nfa(almost_last_nfa);
    return 0;
  } 
  return 1;
}

// Checks if the first non-whitespace character is an operation. Complements empty_stack_check
void zero_index_operator(){
  printf("There is an operator at the beginning of the test file.\n");
  exit(1);
}
