### Mistakes:
1. the addition between two big numbers is in O(n^2)

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

5. a input restriction for the real numbers: the periodic numbers will only be available as a computations' result, never as an input.

6. reduction function, for rational numbers. for the real numbers it is packed with a calculation function which will take care of the period

- period will be represented by ()
- fraction => real number with period
- real number with period => fraction

7. i was wrong with the implementation of the second number
- C should contain 2 basic_number pointers

8. simple numbers = int, float, etc
- constructor from simple number to basic_number
- constructor from const char* to basic_number
- operator int() and float() from basic_number to simple number
- conversion function from simple number to const char*

9. a float will be converted to basic_number with only two floating points
0. it is not the duty of a natural number to simplify a rational / real number