# Regex to NFA 

This program reads from STDIN a series of characters representing the alphabet of a finite automaton (a,b,c,d,e) and 
the characters representing regular expression operations (concatenation: &, kleene star: *, union: |), creating a 
corresponding NFA.
<br>

Parsing and error checking exists to make sure the expression is complete. The NFA is constructed piecemeal using a stack
which builds smaller NFAs into larger ones until only one remains on the stack.
<br>

The program prints the transition functions for each node in the NFA before terminating.
<br>

The input must be in postfix notation.
<br>

## Examples

This is the NFA representation of a&b (a concatenated with b), presented in postfix notation as ab&.
<br>
S denotes the beginning state. F denotes the final state.
<br>

![image](./screenshots/concat_example.png)

Complexity is limited only by the given alphabet, operations, and machine memory.
![image](./screenshots/bigger_nfa.png)

## Compilation
"make" produces a "main" executable file.
