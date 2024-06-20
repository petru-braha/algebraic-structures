#pragma once
#include "digit_node.h"
//#define max_bytes 3GB

#define first_number 0 // for bool parameters
#define secnd_number 1

class basic_number // the most general number, abstract class => complex
{
protected:
    digit_node* number0 = nullptr;  // root of the linked list. list goes from right to left
    digit_node* number1 = nullptr;

    // at the end
    digit_node* insert_symbol(const bool& nr, const char& symbol);
    bool        remove_symbol(const bool& nr);

public:
    basic_number();
    basic_number(float nr);   // i want to create a copy of the number, general function, small numbers
    basic_number(float nr0, float nr1);

    basic_number(const char* buffer); // the actual big numbers will be placed with this function
    basic_number(const char* buffer0, const char* buffer1);

    basic_number(const basic_number& nr);
    basic_number(const basic_number&& nr) noexcept;

    digit_node* get_number(const bool& nr) const;
    void print() const;

    //virtual void print() const = 0;
    //virtual ~basic_number() = 0;
};
///basic_number::~basic_number(){}
