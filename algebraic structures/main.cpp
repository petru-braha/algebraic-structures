#include <iostream>
#include "number/digit_node.h"
#include "number/basic_number.h"
#include "number/types/natural_number.h"


int main()
{   
    // declaration
    float real = 12346; // 99999 // si invers
    natural_number x(15), y(5);
    
    // actual testing
    natural_number z;
    z = x + y;
    z.print();
    return 0;
}
