#pragma once
#include "../basic_number.h"

class natural_number : public basic_number
{
    typedef const natural_number& n_nr;
public:
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
    void print() const;
    ~natural_number();
};

basic_number cast_float(basic_number& nr);