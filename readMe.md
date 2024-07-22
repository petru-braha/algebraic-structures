# Algebra

## TO DO / actual strategy:
- i have doubts about the implementation of the numbers. i will now focus only on sets
- after implementing sets, i will focus on building the second version of my numbers

### Purpose:

- finite sets: check subsets and properties
- infinite structures: check properties, find formula
- finite structures: the most important (Zn, Fn)

- types of structures: semi-groups, monoids, groups, rings, division rings, integral domain, fields, vector spaces

- computations: multiplying values / is the result in the structure
- commutativity
- check if it is closed
- check if it is a subgroup / field

### Implementation:
- it is not that important to be stingy about the memory (taking into account this article: https://www.quora.com/What-is-the-practical-use-for-large-numbers-with-an-extremely-high-amount-of-digits-millions)
- extend the number to a maximum capacity of 3GB, where a single digit takes up 1B.
- limit the maximum number of bytes taking into account, how many RAM GB is free.
- good practice! reduce before any operation the fractions
- a primitive float will be represented just with 2 decimals, arbitrary decision

### future development: 
- expression classes, polynomials: vector < [complex_number constant, new type x, int integer] > 
- vector spaces

### what i would do different if i will start a similar project again (version 2):
- i will implement the numbers as an array of digits and not list! in this current vision i ran into 2 problems
	- O(n) - access time of a bit instead of linear. this evolves into O(n^2) - addition between two numbers (not great)
	- the original plan was to build a large number depending on the available space. i wished to maximize the information of a number in small quantities.

	- let's consider the following number: 10
		- can be represented in 4 bytes, as a int
		- can be represented in 2 bytes, as a array of char
		- natural numbers class: total cost of my implementation : 16(first digit node) + 16(second digit node) + 8(the variable "bytes" - unsigned long long int) + 8(vfptr - the virtual table) = 48 bytes == 12 * sizeof((int)10).
	
	- *UPDATE*: i found a better choice!: array of unsigned long long int values (check "version 2.md").