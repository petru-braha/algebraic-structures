# General overview:

### Purpose:

- finite sets: check subsets and properties
- infinite structures: check properties, find formula
- finite structures: the most important (Zn, Fn)

- types of structures: semi-groups, monoids, groups, rings, division rings, integral domain, fields, vector spaces

- multipling values / is the resullt in the structure
- commutative
- check if it is closed
- check if it is a subgroup / field

- do computation in that field

### Implementation:
- extend the number to a maximum capacity of 3GB, where a single digit takes up 1B.
- limit the maximum number of bytes taking into account, how many RAM GB is free.
- good practice! reduce before any operation the fractions
- a primivite float will be represented just with 2 decimals, arbitrary decision

- how a structure will be implemented?
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

### future development: 
- polynomials: vector < [complex_number constant, new type x, int integer] > 
- vector spaces: