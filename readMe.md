# General overview:

### Purpose:

### Implementation:
- extend the number to a maximum capacity of 3GB, where a single digit takes up 1B.
- limit the maximum number of bytes taking into account, how many RAM GB is free.

### Journal:
1. i have decided to not procced with the analysis of infite sets. 
- unpractical 
- no purpose to study them

2. same decision for the infite sets in algebraic structures

3. basic_number == a linked list of digits(stored in logical order)

inversed list:
- add_digit: O(1)
- addition between 2 nr: O(n)
- print: O(2*n)

normal list:
- add_digit: O(1)
- addition between 2 nr: O(n)
- print: O(n)

4. basic_number = abstract class
- has to be general enough
- the complex number with 


// basic_number == complex number / basic_number == real
basic number == complex
has 2 buffers

for N, Z the second one will be empty
for Q, both will be represented by Z
for R, one will be represented by R and the second one will be empty / if it can be reduced then both by Z
for C, both will be represented by R, but there will be an operation of reduction for both (for R, Q there is only one operation of reduction)

in basic number the 2 buffers will be represented by 2 R
restrictions will appear only in child classes
