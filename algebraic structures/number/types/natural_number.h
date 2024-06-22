#pragma once
#include "../basic_number.h"

// trebuie sa ma asigur ca acel rational poate fi scris natural
// orice negativ il trece in modul

class natural_number : public basic_number
{
public:
    natural_number();
    natural_number(float nr);
    natural_number(basic_number* nr);

    basic_number& operator + (const float& nr);
    basic_number& operator + (const basic_number* nr);
    basic_number& operator - (const float& nr);
    basic_number& operator - (const basic_number* nr);

    basic_number& operator * (const float& nr);
    basic_number& operator * (const basic_number* nr);
    basic_number& operator / (const float& nr);
    basic_number& operator / (const basic_number* nr);

    bool operator == (const float& nr);
    bool operator == (basic_number* nr);

    operator int() const; 
    void print() const;
    ~natural_number();
};