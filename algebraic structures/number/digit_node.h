#pragma once
#include <stdio.h>

typedef unsigned long long ull;

class digit_node
{
    char data;
public:
    digit_node* next;

    digit_node() :data(NULL), next(NULL) {}
    digit_node(const char& digit) : data(digit), next(NULL) {}

    void set_data(const char& digit) { data = digit; }
    char get_data() const { return data; }
};