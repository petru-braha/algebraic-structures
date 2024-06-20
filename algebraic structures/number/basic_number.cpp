#include <stdio.h>
#include <stdlib.h>
#include "basic_number.h"

digit_node* null = nullptr;

/*#define concatenate_digit(pointer, digit)\
{\ 
    if(pointer->get_nr() > max_bytes)\
        printf("error - adding digit: no more memory.\n")\
    try{ pointer = new digit_node(digit); } catch(...){} \
}*/

#define error_handeler(msg)\
{ printf("error: %s.\n", msg); exit(EXIT_FAILURE); }

digit_node* basic_number::insert_symbol(const bool& nr, const char& digit)
{
    digit_node* part = nullptr;
    if (nr == first_number) part = number0;
    else part = number1;

    if (part == nullptr)
    {
        part = new digit_node(digit);
        return part;
    }

    digit_node* it = part, *nxt = it->next;
    while (nxt)
    {
        it = nxt;
        nxt = it->next;
    }

    nxt = new digit_node(digit);
    it->next = nxt;
    return it;
}

bool basic_number::remove_symbol(const bool& nr)
{
    digit_node* part = nullptr;
    if (nr == first_number) part = number0;
    else part = number1;

    if (part == nullptr)
        return false;

    digit_node* it = part, *nxt = it->next;
    while (nxt)
    {
        it = nxt;
        nxt = it->next;
    }

    delete it;
    it = nullptr;
    return true;
}

//-------------------------------------------------------------------------------------------
// helper functions:

char last_digit(int& nr)
{
    char last = abs(nr) % 10;
    nr = nr / 10;
    return last + '0';
}

void add_beginng(digit_node*& previous, digit_node*& ptr, const char& symbol)
{
    digit_node* it = new digit_node(symbol);
    it->next = ptr;
    ptr = it;
    if (previous)
        previous->next = ptr;
}

void add_between(digit_node* ptr1, digit_node* ptr2, const int& symbol)
{
    if (ptr1->next != ptr2)
        error_handeler("wrong symbols");

    digit_node* middle = new digit_node(symbol);
    middle->next = ptr2;
    ptr1->next = middle;
}

// constructors:----------------------------------------------------------------------------- 

basic_number::basic_number()
{
    number0 = new digit_node('0');
    number1 = new digit_node('0');
}

basic_number::basic_number(float nr)
{
    number1 = new digit_node('0');
    int integer = (int)nr; 

    // concatenate integer 
    number0 = new digit_node(last_digit(integer));
    while (integer)
       add_beginng(null, number0, last_digit(integer));
    if (nr < 0) add_beginng(null, number0, '-');
    
    nr -= int(nr);
    if (nr == 0) return;

    insert_symbol(first_number, '.');
    while (nr != (int)nr) // problem !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        nr *= 10;

    // concatenate float points
    integer = (int)nr;
    digit_node* ptr = insert_symbol(first_number, last_digit(integer));
    
    while (integer)
        add_beginng(ptr, ptr->next, last_digit(integer));
}

basic_number::basic_number(float nr0, float nr1) : basic_number(nr0)
{
    remove_symbol(secnd_number);
    int integer = (int)nr1;

    // concatenate integer to number1
    number1 = new digit_node(last_digit(integer));
    while (integer)
        add_beginng(null, number1, last_digit(integer));
    if (nr1 < 0) add_beginng(null, number1, '-');

    nr1 -= integer;
    if (nr1 == 0) return;

    insert_symbol(secnd_number, '.');
    while (nr1 != (int)nr1)
        nr1 *= 10;

    // concatenate float points
    integer = (int)nr1;
    digit_node* ptr = insert_symbol(secnd_number, last_digit(integer));
    while (integer)
        add_beginng(ptr, ptr->next, last_digit(integer));
}

basic_number::basic_number(const char* buffer)
{
    size_t index = 0;
    while (buffer[index])
    {
        insert_symbol(first_number, buffer[index]);
        index++;
    }

    insert_symbol(secnd_number, '0');
}

basic_number::basic_number(const char* buffer0, const char* buffer1)
{
    size_t index = 0;
    while (buffer0[index])
    {
        insert_symbol(first_number, buffer0[index]);
        index++;
    }

    index = 0;
    while (buffer1[index])
    {
        insert_symbol(secnd_number, buffer1[index]);
        index++;
    }
}

// copy and move constructor

basic_number::basic_number(const basic_number& nr)
{
    digit_node* it = nr.get_number(0);
    
    while (it)
    {
        this->insert_symbol(0, it->get_data());
        it = it->next;
    }

    it = nr.get_number(1);
    while (it)
    {
        this->insert_symbol(1, it->get_data());
        it = it->next;
    }
}

basic_number::basic_number(const basic_number&& nr) noexcept : basic_number(nr)
{
    delete &nr;
}

//-------------------------------------------------------------------------------------------
// constant functions: 

void basic_number::print() const // has to be pure 
{
    printf(" ");
    
    digit_node* it = number0;
    
    while (it)
    {
        printf("%c", it->get_data());
        it = it->next;
    }

    printf("/");
    
    it = number1;
    while (it)
    {
        printf("%c", it->get_data());
        it = it->next;
    }

    printf(" ");
}

digit_node* basic_number::get_number(const bool& nr) const
{
    if (nr == 0) return number0;
    return number1;
}
