#include <iostream>
#include "number/digit_node.h"
#include "number/basic_number.h"
#include "number/types/natural_number.h"    



int main()
{   
    // declaration
    float real = 3; // 99999 // si invers
    natural_number x(3), y(555);
    
    // actual testing
    natural_number z(2000);
    z = z * x;
    z.print();
    return 0;
}

