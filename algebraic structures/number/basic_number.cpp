#include <stdio.h>
#include <stdlib.h>
#include <limits>
#include "basic_number.h"
#pragma warning(disable: 4996)

int concatenation(digit_node*& ptr, const char& symbol, ull& bytes)
{
    bytes++;
    if (bytes >= max_bytes)
    {
        error_handeler("no more memory"); // failure
        exit(1);
    }

    ptr = new digit_node(symbol);
    return 0; // succes
}

//void operator"" _digits(const char)

digit_node* null = nullptr;
digit_node* basic_number::insert_symbol(const char& digit)
{
    if (number == nullptr)
    {
        concatenation(number, digit, bytes);
        return number;
    }

    if (number->get_data() == '0' && number->next == nullptr)
    {
        delete number;
        concatenation(number, digit, bytes);
        return number;
    }

    digit_node* it = number, *nxt = it->next;
    while (nxt)
    {
        it = nxt;
        nxt = it->next;
    }

    concatenation(nxt, digit, bytes);
    it->next = nxt;
    return it;
}

digit_node* basic_number::insert_symbol(digit_node* previous, const char& symbol)
{
    if (previous == nullptr)
        return nullptr;
    if (previous->next)
        previous->next->set_data(symbol);
    else concatenation(previous->next, symbol, this->bytes);
    return previous->next;
}

bool basic_number::remove_symbol()
{
    if (number == nullptr)
        return false;

    digit_node* it = number, *nxt = it->next;
    while (nxt)
    {
        it = nxt;
        nxt = it->next;
    }

    delete it;
    it = nullptr;
    bytes--;
    return true;
}

bool basic_number::remove_symbol(const ull& pos)
{
    digit_node* it = number, * nxt = number->next;
    if (pos == 0)
    {
        number = number->next;
        delete it;
        return true;
    }

    for (ull i = 1; i < pos && nxt; i++)
    {
        it = nxt;
        nxt = nxt->next;
    }

    if (nxt == NULL)
        return false;

    it->next = nxt->next;
    delete nxt;
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

void add_beginng(digit_node*& ptr, const char& symbol)
{
    digit_node* it = new digit_node(symbol);
    it->next = ptr;
    ptr = it;
}

void add_beginng(digit_node*& previous, digit_node*& ptr, const char& symbol)
{
    digit_node* it = new digit_node(symbol);
    it->next = ptr;
    ptr = it;
    if (previous)
        previous->next = ptr;
}

int add_between(digit_node*& ptr1, digit_node* ptr2, const int& symbol)
{
    if (ptr1->next != ptr2)
        error_handeler("wrong symbols"); // failure

    digit_node* middle = new digit_node(symbol);
    middle->next = ptr2;
    ptr1->next = middle;
    return 0; // succes
}

// constructors:----------------------------------------------------------------------------- 

basic_number::basic_number()
{
    bytes = 0;
    concatenation(number, '0', bytes);
}

basic_number::basic_number(float nr)
{
    bytes = 0;
    int integer = (int)nr;

    // concatenate integer 
    concatenation(number, last_digit(integer), bytes);
    while (integer){
        add_beginng(null, number, last_digit(integer));
        bytes++;
    }
    if (nr < 0) { add_beginng(null, number, '-'); bytes++; }
    
    nr -= int(nr);
    if (nr == 0) return;

    insert_symbol('.');
    int i = 0;
    while (nr != (int)nr && i++ < 2) // problem !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        nr *= 10;

    // concatenate float points
    integer = (int)nr;
    digit_node* ptr = insert_symbol(last_digit(integer));

    while (integer)
    {
        add_beginng(ptr, ptr->next, last_digit(integer));
        bytes++;
    }
}

basic_number::basic_number(float nr0, float nr1) : basic_number(nr0)
{
    int integer = (int)nr1;
    insert_symbol('/');
    if (nr1 < 0)
        insert_symbol('-');

    digit_node* ptr = insert_symbol(last_digit(integer));
    while (integer)
    {
        add_beginng(ptr, ptr->next, last_digit(integer));
        bytes++;
    }
    
    nr1 -= int(nr1);
    if (nr1 == 0) return;

    insert_symbol('.');
    int i = 0;
    while (nr1 != (int)nr1 && i++ < 2)
        nr1 *= 10;

    // concatenate float points
    integer = (int)nr1;
    ptr = insert_symbol(last_digit(integer));
    while (integer)
    {
        add_beginng(ptr, ptr->next, last_digit(integer));
        bytes++;
    }
}

basic_number::basic_number(const char* buffer)
{
    size_t index = 0;
    while (buffer[index])
    {
        insert_symbol(buffer[index]);
        index++;
    }
}

basic_number::basic_number(const char* buffer0, const char* buffer1)
{
    size_t index = 0;
    while (buffer0[index]) // && index < max_bytes/2
    {
        insert_symbol(buffer0[index]);
        index++;
    }
    
    ull bytes_available = max_bytes - index;
    if (bytes_available <= 3)
        return;
    digit_node* ptr = number;

    insert_symbol('/');
    index = 0; 
    while (buffer1[index] && index < bytes_available)
    {
        ptr = insert_symbol(buffer1[index]);
        index++;
    }

    // patch
    ptr = ptr->next;
    if (ptr->get_data() == '.')
    {
        delete ptr->next;
        ptr->next = nullptr;
    }
}

// copy and move constructor

basic_number::basic_number(const basic_number& nr)
{
    digit_node* it = nr.get_number();
    
    while (it)
    {
        this->insert_symbol(it->get_data());
        it = it->next;
    }
}

basic_number::basic_number(const basic_number&& nr) noexcept : basic_number(nr)
{
    delete &nr;
}
/*
const basic_number& basic_number::operator = (float& nr)
{
    reinitialise(number);
    bytes = 0;
    int integer = (int)nr;

    // concatenate integer 
    insert_symbol(last_digit(integer));
    while (integer) {
        add_beginng(null, number, last_digit(integer));
        bytes++;
    }
    if (nr < 0) { add_beginng(null, number, '-'); bytes++; }

    nr -= int(nr);
    if (nr == 0) return *this;

    insert_symbol('.');
    int i = 0;
    while (nr != (int)nr && i++ < 2) // problem !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        nr *= 10;

    // concatenate float points
    integer = (int)nr;
    digit_node* ptr = insert_symbol(last_digit(integer));

    while (integer)
    {
        add_beginng(ptr, ptr->next, last_digit(integer));
        bytes++;
    }

    return *this;
}
/*
basic_number& basic_number::operator = (const basic_number& nr)
{
    digit_node* it_nr = nr.get_number();
    nr.print();
    reinitialise(number);
    bytes = 0;

    char digit = it_nr->get_data();
    insert_symbol(digit);
    
    digit_node* it = number;
    while (it_nr)
    {
        char digit = it_nr->get_data();
        insert_symbol(it, digit);
        it_nr = it_nr->next;
        it = it->next;
    }

    return *this;
}
*/
//-------------------------------------------------------------------------------------------
// constant functions:

digit_node* basic_number::get_number() const
{
    return number;
}

ull basic_number::get_bytes() const
{
    return bytes;
}

// helper functions:
inline int digits_number(ull nr)
{
    int digits = 0;
    while (nr)
    {
        nr /= 10;
        digits++;
    }

    return digits;
}

// conversion:

basic_number::operator int() const
{
    if (number == nullptr)
        return 0;
    if (number->next == nullptr)
    {
        if (number)
            return number->get_data() - '0';
        return 0;
    }
    
    // check if the denominator is negative
    if(number->get_data() == '-')
        digit_node* it = number->next;
    digit_node* it = number;

    int nr0 = 0, nr1 = 0;
    while (it)
    {
        if (it->get_data() == '.' || it->get_data() == '/')
            break;
        nr0 = nr0 * 10 + (it->get_data() - '0');
        it = it->next;

        if (digits_number(nr0) == digits_number(INT_MAX))
            error_handeler("conversion to int is not possible");
    }

    // in case it is NOT a fraction we end the computation here
    if (number->get_data() == '-')
        nr0 *= -1;
    if (it == nullptr)
        return nr0;

    // traverse until i find the nominator
    while(it->get_data() != '/')
       it = it->next;
    it = it->next;
    
    // check if the nominator is negative
    if (it->get_data() == '-')
        digit_node* nxt = it->next;
    digit_node* nxt = it;

    while (nxt)
    {
        if (nxt->get_data() == '.')
            break;
        nr1 = nr1 * 10 + (nxt->get_data() - '0');
        nxt = nxt->next;

        if (digits_number(nr1) == digits_number(INT_MAX))
            error_handeler("conversion to int is not possible");
    }

    if (it->get_data() == '-')
        nr1 *= -1;

    return nr0 / nr1;
}

basic_number::operator float() const
{
    if (number == nullptr)
        return 0;
    if (number->next == nullptr)
    {
        if (number)
            return float(number->get_data() - '0');
        return 0;
    }

    // check if the denominator is negative
    if (number->get_data() == '-')
        digit_node* it = number->next;
    digit_node* it = number;

    int nr0 = 0, nr1 = 0;
    bool decimal = false;
    int p = 1;
    while (it)
    {
        if (it->get_data() == '/')
            break;
        if (it->get_data() == '.')
            decimal = true;
        else
            nr0 = nr0 * 10 + (it->get_data() - '0');
        it = it->next;

        if (decimal)
            p *= 10;

        if (digits_number(nr0) == digits_number(INT_MAX))
            error_handeler("conversion to int is not possible");
    }

    // in case it is NOT a fraction we end the computation here
    nr0 /= p;
    if (number->get_data() == '-')
        nr0 *= -1;
    if (it == nullptr)
        return (float)nr0;

    // traverse until i find the nominator
    it = it->next;

    // check if the nominator is negative
    if (it->get_data() == '-')
        digit_node* nxt = it->next;
    digit_node* nxt = it;

    p = 1;
    decimal = false;
    while (nxt)
    {
        if (nxt->get_data() == '.')
            decimal = true;
        else
            nr1 = nr1 * 10 + (nxt->get_data() - '0');
        nxt = nxt->next;

        if (decimal)
            p *= 10;

        if (digits_number(nr1) == digits_number(INT_MAX))
            error_handeler("conversion to int is not possible");
    }

    nr1 /= p;
    if (it->get_data() == '-')
        nr1 *= -1;

    return float(nr0 / nr1);
}

#include <string>
const char* convert_float(float nr)
{
    char* buffer = new char[20];
    int integer = abs(int(nr));

    std::string result = "";
    if (nr < 0)
        result += '-';
    while (integer)
    {
        result += integer % 10 + '0';
        integer /= 10;
    }
    
    nr -= (int)nr; 
    if (nr == 0)
    {
        strcpy(buffer, result.c_str());
        return buffer;
    }

    int i = 0;
    while (nr != (int)nr && i++ < 2)
        nr *= 10;

    integer = int(nr);

    while (integer)
    {
        result += (integer % 10 + '0');
        integer /= 10;
    }

    strcpy(buffer, result.c_str());
    return buffer;
}

digit_node* basic_number::get_digit(ull i) const
{
    digit_node* it = number;
    while (i && it)
    {
        i--;
        it = it->next;
    }

    if (i)
        return nullptr;
    return it;
}

inline int bytes_number(float nr)
{
    int bytes = 0;
    if (nr < 0)
        bytes++;
    int i = 0;
    while (nr != (int)nr && i++ < 2) // accepting only two floating points
        bytes++;
        
    while (nr > 10)
    {
        bytes++;
        nr /= 10;
    }

    bytes++; // last digit before the point
    return bytes;
}

void reinitialise(digit_node*& root)
{
    digit_node* root_copy = root;
    while (root_copy)
    {
        digit_node* it = root_copy->next;
        delete root_copy;
        root_copy = it;
    }

    root = new digit_node('0');
}
