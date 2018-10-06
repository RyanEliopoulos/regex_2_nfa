#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

//####################################//
//           Structs                  // 
//####################################//
struct nFA{
  int start_state;
  int final_state;
  struct transition_node* trans_list;
};

struct transition_node{
  int origin_state;
  int destination_state;
  int symbol;
  struct transition_node* next_transition;
};

struct stack_node{
  struct nFA* nfa;
  struct stack_node* next;
};

//#######################################
//######## Function definitions #########
//#######################################

//######################################//
//            nfaBuilder.c              //
//**************************************//
struct nFA* build_nfa_from_char(int symbol);
void modify_nfa_union(struct nFA* NFA1, struct nFA* NFA2);
void modify_nfa_concatenation(struct nFA* NFA1, struct nFA* NFA2);
void modify_nfa_kleene_star(struct nFA* target_nfa);
void join_transition_list(struct transition_node*, struct transition_node*);
struct transition_node* list_init(int origin, int destination, int symbol);

//######################################//
//                stack.c               //
//**************************************//
struct nFA* pop(struct stack_node* sentinel);
int push(struct stack_node* sentinel, struct nFA* pushed_nfa);
struct stack_node* stack_init();
void free_stack(struct stack_node*);

//########################################//
//              core.c                    //
//******************************************
void build_nfa(struct stack_node* sentinel);
int empty_stack_check(int, struct nFA*, struct nFA*);
void zero_index_operator();
void ending_stack_check(struct stack_node*);

//######################################//
//            main.c                    //
//**************************************//
void print_transitions(struct nFA*);

//######################################//
//          ancillary.c                 //
//**************************************//
void free_nfa(struct nFA*);
void print_transitions_one_line(struct nFA*);

