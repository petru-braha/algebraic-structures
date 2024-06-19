#pragma once
#include "digit_node.h"

class basic_number
{
    digit_node* number; // root of the linked list. list goes from right to left

    bool insert_digit(const char& digit);
    bool remove_digit(const char& digit);

public:
    basic_number(){}
    basic_number(const ull& nr);

    basic_number(const basic_number& nr);
    basic_number(const basic_number&& nr);

    basic_number& operator + (const ull& nr);
    basic_number& operator + (const basic_number& nr);

    basic_number& operator - (const ull& nr);
    basic_number& operator - (const basic_number& nr);

    basic_number& operator * (const ull& nr);
    basic_number& operator * (const basic_number& nr);

    basic_number& operator / (const ull& nr);
    basic_number& operator / (const basic_number& nr);

    bool operator == (const ull& nr);
    bool operator == (const basic_number& nr);

    basic_number& operator += (const ull& nr);
    basic_number& operator += (const basic_number& nr);

    basic_number& operator -= (const ull& nr);
    basic_number& operator -= (const basic_number& nr);

    basic_number& operator *= (const ull& nr);
    basic_number& operator *= (const basic_number& nr);
    
    basic_number& operator /= (const ull& nr);
    basic_number& operator /= (const basic_number& nr);

    operator int() const;
    operator ull() const;
    void print() const;
    ull  number_digits() const;

    virtual ~basic_number() = 0;
};
basic_number::~basic_number(){}
