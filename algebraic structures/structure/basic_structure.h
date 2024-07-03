#pragma once
#include "finite_set.h"
#include "operation.h"
#include "finite_set.h"

template <class numbers = basic_number>
class basic_structure : public finite_set<numbers>, operation<numbers>
{
public:
    basic_structure();
    basic_structure();
    basic_structure();
	//bool closure();

    ~basic_structure();
};

class semi_group;
class monoid;
class group;
class ring;
class field; // skew fields and commutative division rings


/*
- how a structure will be implemented?
template <class number_type = basic_number>
Structure : public N , public // etc
{
    std::vector<>
    // check if the type coresponds limit the classes that can determine what kind of numbers can be placed here
    // operation (int (*f)()) i should be able to define a function as operation // the default one should be + / *
public:
    constructor(N value)
    constructor(string)

}
*/