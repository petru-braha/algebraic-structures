#pragma once
#include "../basic_number.h"

class natural_number : public basic_number
{
    typedef const natural_number& n_nr;
public:                                             // pay attention: nr is always converted! see operator*!!!!!
    natural_number();
    natural_number(float nr);
    natural_number(const basic_number& nr);

    n_nr operator = (float& nr);
    n_nr operator = (const natural_number& nr);
    
    n_nr operator + (const float& nr);
    n_nr operator + (const basic_number& nr);
    n_nr operator - (const float& nr);
    n_nr operator - (const basic_number& nr);

    n_nr operator * (const float& nr); 
    n_nr operator * (const basic_number& nr);
    n_nr operator / (const float& nr);
    n_nr operator / (const basic_number& nr);

    bool operator == (const float& nr);
    bool operator == (const basic_number& nr);

    operator int() const; 
    ull get_digits() const; // for other classes this method will be diffrent. of course here it is equivalent to get_bytes.
    void print() const;
    ~natural_number();
};

float cast_float(float nr);