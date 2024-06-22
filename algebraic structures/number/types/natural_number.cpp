#include <stdio.h>
#include <stdlib.h>
#include "natural_number.h"

//---------------------------------------------------------------------------------------------------
// constructors:

natural_number::natural_number() : basic_number() {}
natural_number::natural_number(float nr) : basic_number(nr)
{
    bytes = 0;
    int integer = (int)nr;

    concatenation(number, last_digit(integer), bytes);
    while (integer) 
    {
        add_beginng(number, last_digit(integer));
        bytes++;
    }
}

natural_number::natural_number(basic_number* nr) // should not be done by casting to float int (what if the number is bigger than INT_MAX?)
{
    bytes = 0;
    if (nr == nullptr || nr->get_number() == nullptr)
    {
        concatenation(number, '0', bytes);
        return;
    }

    digit_node* it = nr->get_number();
    if (it->get_data() == '-')
        it = it->next;

    while (it)
    {
        concatenation(this->number, it->get_data(), this->bytes);
        it = it->next;
    }
}

//---------------------------------------------------------------------------------------------------
// operators:

basic_number& natural_number::operator + (const float& nr)
{
    // operator -
    if (nr < 0)
    {
        *this - nr;
        return *this;
    }

    int integer = int(nr);
    while (integer)
    {
        add_beginng(number, last_digit(integer));
        bytes++;
    }

    return *this;
}

basic_number& natural_number::operator + (const basic_number* nr)
{
    // operator -
    if (nr->get_number()->get_data() == '-')
    {
        *this - nr;
        return *this;
    }

    // delete floating points
    ull n_nr = 0;

    digit_node* it = nr->get_number();
    while (it->get_data() != '.' && it)
    {
        it = it->next;
        n_nr++;
    }
    
    // addition with a natural number
    ull n = this->bytes > n_nr ? this->bytes : n_nr;
    char carry = 0;

    while (n)
    {
        n--;
        n_nr--;
        digit_node* it = this->get_digit(n);
        digit_node* it_nr = nr->get_digit(n_nr);
        bool flag = false;

        char d1 = it->get_data(), d2 = it_nr->get_data(), D = d1 + d2 - 2 * '0';
        if (D >= 10)
        {
            D = D % 10;
            flag = true;
        }
        
        D += '0';
        it->set_data(D + carry);
        carry = flag == true ? 1 : 0;
    }

    if (carry)
        add_beginng(number, '1');
    return *this;
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

basic_number& natural_number::operator - (const float& nr)
{
    // operator +
    if (nr < 0)
    {
        *this + (-1) * nr;
        return *this;
    }

    if (digits_number(int(nr)) > this->bytes)
    {
        // delete number
        // add 0
    }

    int integer = int(nr);
    while (integer)
    {
        add_beginng(number, last_digit(integer));
        bytes++;
    }


    return *this;

}

basic_number& natural_number::operator - (const basic_number* nr)
{
    return *this;

}

basic_number& natural_number::operator * (const float& nr)
{
    natural_number copy(this);
    for (int i = 0; i < nr; i++)
        *this + copy;
    
    if (nr < 0)
        add_beginng(number, '-');
    //nr = nr - (int)nr;
    return *this;
}

basic_number& natural_number::operator * (const basic_number* nr)
{

    return *this;
}

basic_number& natural_number::operator / (const float& nr)
{
    return *this;
}

basic_number& natural_number::operator / (const basic_number* nr)
{
    return *this;
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

bool natural_number::operator == (const float& nr)
{
    if ((nr < 0 && number->get_data() != '-') || (nr > 0 && number->get_data() == '-'))
        return false;

    int integer = (int)nr;
    if (this->bytes != digits_number(integer))
        return false;

    int power = 1;
    while (power * 10 <= integer)
        power *= 10;

    digit_node* it = number;
    while (integer)
    {
        char digit = integer / power + '0';
        if (digit != it->get_data())
            return false;

        integer /= 10;
        power /= 10;
        it = it->next;
    }

    return true;
}

bool natural_number::operator == (basic_number* nr)
{
    if (this->bytes != nr->get_bytes() || nr->get_number()->get_data() == '-')
        return false;

    digit_node* it = number, * it_nr = nr->get_number();
    while (it)
    {
        if (it->get_data() != it_nr->get_data())
            return false;

        it = it->next;
        it_nr = it_nr->next;
    }

    return true;
}

//---------------------------------------------------------------------------------------------------
// constant functions:

natural_number::operator int() const
{
    int result = int(*this);
    if (result == -1) 
        return -1;
    return abs(result);
}

void natural_number::print() const
{
    digit_node* it = number;
    while (it)
    {
        printf("%c", it->get_data());
        it = it->next;
    }

    printf(" ");
}

natural_number::~natural_number()
{
    while (number)
    {
        digit_node* it = number->next;
        delete number;
        number = it;
    }
}