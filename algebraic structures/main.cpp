#include <iostream>
#include "number/digit_node.h"
#include "number/basic_number.h"
#include "number/types/natural_number.h"

/*
void reduction();
void calculate();
void write_as_fraction();
*/
int main()
{   
    float real = 5;
    natural_number x(5), y(5);
    x + y;
    //x - real;
    x.print();
    
    y = &(x + real);
    x.print();
    y.print();
    return 0;
}
