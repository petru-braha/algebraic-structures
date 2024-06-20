#include <iostream>
#include "number/digit_node.h"
#include "number/basic_number.h"

int f(float nr)
{
    while (nr != (int)nr)
        nr *= 10;
    return nr;
}

int main()
{   
    std::cout << f(0.0001);
}

// TO DO:
// child classes derived from basic_number

// maximum bytes search, concatenation function for basic_number

// finite sets: verific subsets, prorpietati
// infite structures: verific proprietati, vad o forma generala a elementelor
// finite structures: mult mai concret 

// semi-groups, monoid, groups, rings, division rings, integral domain, fields

// Zn , Fn
// vector spaces


/* 


Class natural_number
just a number
that can respect the properties of natural numbers

template <class type_of_number>
Structure : public N , public // etc 
{   
    // type_of_number vector 
    // check if the type coresponds limit the classes that can determine what kind of numbers can be placed here
    // operation (int (*f)()) i should be able to define a function as operation // the default one should be + / *
public:
    constructor(N value)
    constructor(string)
    ~
}

for fields i have to implements poly
// determine if it is ireductible


purpose:
-multipling values / is the resullt in the structure
-commutative
-check if it is closed
-check if it is a subgroup / field

- do computation in that field



*/