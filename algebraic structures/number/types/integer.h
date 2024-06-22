#pragma once
#include "../basic_number.h"

// trebuie sa ma asigur ca acel rational poate fi scris natural
// orice negativ il trece in modul

class integer : public basic_number
{
public:
    integer();
    integer(float nr);
    integer(basic_number* nr);

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

    operator int() const; // la fel ca cel origin dar! in modul
    operator float() const;

    void print() const;
    ~integer();
};