### Disclaimer: it seems pointless to consider very large numbers, but my ambition aims for greater science.

## Analysis data structure:
+ a number has to be an set of digits with fixed index
+ variable number of digits
+ each digit has just one succesor
+ interested in: searching, inserting and removing; NOT sorting or random access

* the operations needed for the digits of the number are: access, insert_front, remove_front
* why just front? constructors and operations

```
			char array		char linked list			inversed char array	inversed char list
access of a digit	O(1)			O(n)					O(1)			O(n)
insert_front		O(n)			O(1)					O(1)			O(1) // with help
remove_front		O(n)			O(1)					O(1)			O(1) // with help
size			n*size(type)		n*( 8(next-pointer) + size(type) )	n*size(type)		n*( 8(next-pointer) + size(type) )
maximum size		user dependent (if)	hardware dependent			user dependent (if)	hardware dependent
```

* maximum size of the array will be preprocessed by the compiler so this version wouldn't have any issues
- if there exists a big amount of contiguous memory: the inversed char array beats the game. else char linked list is still an option

## Analysis type:
* there will be a byte to determine the sign
```
1. primitives	ULL		UL		US		UC 
max_value 18446744073709551615 	4294967295	65535 		255
bytes		8		4		2		1
digits		20		10		5		3
max_digits	19		9		4		2
```
- max_digits == how many digits can actually have any value from {0, 1, ... , 9}
- for primitives it is better to user their type (less bytes in all cases)

2. large number 19000 digits? best choice?
-ULL - 1000 numbers => 8000 bytes
-UC  - 9500 numbers => 9500 bytes

3. hypothesis: for large amounts of digits, the most efficient type would be ULL for an array (//demonstration)


## Ranking and final analysis
- inversed ULL array? pointless the complexities will be high enough
```
			inversed char array	ULL array	char linked list

access of a digit	O(1)			O(1) + c	O(n)
insert_front		O(1)			O(1) + c	O(1)
remove_front		O(1)			O(1) + c	O(1)
size			n*nr_digits		best		worst
maximum size		(if)			(if)		available

comments		best time		best memory	backup plan
```

## Conclusion:
- by "char <data structure>" i mean a single digit by a char, NOT 2 digits to be represented by a char.
- version 1 == char linked list
- version 2 == inversed char array
- version 3 == ULL array

- my program will have to image a very large limit of digits (e.g. 3*10^10). firstly, it will convert this number of digits into bytes for an 'inversed char array'. then will ask the O.S. is this quantity available contiguously? if yes we will build 'version 2'. if not, convert into bytes for an 'ULL array'. if the answer is still negative... what remains to do is the backup plan, aka. version 1.