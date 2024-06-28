#pragma once
#include "../basic_number.h"

class natural_number : public basic_number
{
public:
    natural_number();
    natural_number(float nr);
    natural_number(basic_number* nr);

    //void operator = (float& nr);
    natural_number& operator = (const basic_number* nr);
    //operator natural_number();

    basic_number& operator + (const float& nr);
    basic_number& operator + (const basic_number& nr);
    basic_number& operator - (const float& nr);
    basic_number& operator - (const basic_number& nr);

    basic_number& operator * (const float& nr);
    basic_number& operator * (const basic_number& nr);
    basic_number& operator / (const float& nr);
    basic_number& operator / (const basic_number& nr);

    bool operator == (const float& nr);
    bool operator == (basic_number* nr);

    operator int() const; 
    void print() const;
    ~natural_number();
};

basic_number cast_float(basic_number& nr);