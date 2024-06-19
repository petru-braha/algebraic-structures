#pragma once
#include <type_traits>

class digit_node
{
    char data;
    digit_node* next;
public:
    digit_node():data(NULL), next(NULL){}
    digit_node(const char& digit): data(digit), next(NULL){}

    void insert(const char& digit);
    void remove(const char& digit);

    char get_data();
    ~digit_node();
};

class basic_number
{
    digit_node* number;
public:
    basic_number(){}
    basic_number();
    basic_number& operator *= (int nr);
    void print() const ;
};


class natural_number;
class integer;
class ratioal_number;
class real_number;
class complex_number; 