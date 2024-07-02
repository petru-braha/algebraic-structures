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

natural_number::natural_number(const basic_number& nr) // should not be done by casting to float int (what if the number is bigger than INT_MAX?)
{
    bytes = 0;
    if (nr.get_number() == nullptr)
    {
        concatenation(number, '0', bytes);
        return;
    }

    digit_node* it = nr.get_number();
    if (it->get_data() == '-')
        it = it->next;

    while (it)
    {
        concatenation(this->number, it->get_data(), this->bytes);
        it = it->next;
    }
}

const natural_number& natural_number::operator = (float& nr)
{
    int integer = abs((int)nr), n = digits_number(integer);
    reinitialise(number);
    insert_symbol(last_digit(integer));

    while (integer)
        add_beginng(number, last_digit(integer));
    
    bytes = n;
    return *this;
}

const natural_number& natural_number::operator = (const natural_number& nr)
{
    reinitialise(number);
    digit_node* it = number, * it_nr = nr.get_number();

    it = insert_symbol(it_nr->get_data());
    it_nr = it_nr->next;

    while (it_nr)
    {
        it = insert_symbol(it, it_nr->get_data());
        it_nr = it_nr->next;
    }
    
    bytes = nr.bytes;
    return *this;
}

//---------------------------------------------------------------------------------------------------
// operators:

const natural_number& natural_number::operator + (const float& nr)
{
    // operator -
    if (nr < 0)
        return *this - nr;
    
    // delete floating points
    int integer = abs(int(nr));

    // addition with a natural number
    natural_number* this_number = new natural_number(*this); // making a copy of it
    ull b = this->bytes - 1;
    char carry = 0;
    bool flag = true; // represents if b != -1
    
    while (integer)
    {
        if (flag == false)
            add_beginng(this_number->number, '0');
        digit_node* actual = this_number->get_digit(b);
        char digit = last_digit(integer) - '0' + actual->get_data() - '0' + carry;
        
        actual->set_data(digit % 10 + '0');
        carry = digit / 10;

        if (b) b--;
        else flag = false;
    }
    
    while (carry && flag) // number > integer
    {
        digit_node* actual = this_number->get_digit(b);
        char digit = actual->get_data() - '0' + carry;

        actual->set_data(digit % 10 + '0');
        carry = digit / 10;

        if (b) b--;
        else flag = false;
    }

    if (carry && flag == false)
        add_beginng(this_number->number, '1');

    return *this_number;
}

const natural_number& natural_number::operator + (const basic_number& nr)
{
    // operator -
    if (nr.get_number()->get_data() == '-')
        return *this - nr;

    // delete floating points
    ull n_nr = 0;
    digit_node* it = nr.get_number();
    while (it && it->get_data() != '.')
    {
        it = it->next;
        n_nr++;
    }

    // addition with a natural number
    ull n = this->bytes;
    char carry = 0;
    natural_number* this_number = new natural_number(*this); // making a copy of it
    bool flag = true; // represents if n != -1
    
    while (n_nr)
    {
        if (n) n--;
        else flag = false;
        n_nr--;

        if(flag == false) add_beginng(this_number->number, '0');

        digit_node* it = this_number->get_digit(n);
        digit_node* it_nr = nr.get_digit(n_nr);

        char d1 = it->get_data(), d2 = it_nr->get_data(), D = d1 + d2 - 2 * '0' + carry;
        it->set_data(D % 10 + '0');
        carry = D / 10;
    }
    
    flag = (n == 0) ? false : true; // patch for small numbers
    while (carry && flag) // number > integer
    {
        if (n) n--;
        else { flag = false; add_beginng(this_number->number, '0'); }
  
        digit_node* actual = this_number->get_digit(n);
        char digit = actual->get_data() - '0' + carry;

        actual->set_data(digit % 10 + '0');
        carry = digit / 10;
    }

    if (carry && flag == false)
        add_beginng(this_number->number, '1');

    return *this_number;
}

const natural_number& natural_number::operator - (const float& nr)
{
    // operator +
    if (nr < 0)
        return *this + (-1) * nr;

    // nr greater than this->number
    if (digits_number(int(nr)) > this->get_digits())
        return *(new natural_number);

    // delete floating points
    int integer = abs(int(nr));
   
    // subtraction with a natural number
    natural_number* this_number = new natural_number(*this);
    ull b = this->bytes - 1;
    char carry = 0;
    bool flag = true;

    while (integer)
    {
        digit_node* actual = this_number->get_digit(b);
        char digit = (actual->get_data() - '0') - (last_digit(integer) - '0') - carry;
        if (digit < 0)
        {
            digit = 10 + digit;
            carry = 1;
        }
        else carry = 0;

        actual->set_data(digit + '0');

        if (b && integer) b--;
        else flag = false;
    }

    if (carry && b == 0 && integer == 0)
        return *(new natural_number);
    if (flag == false) b--;
    while (carry)
    {
        digit_node* actual = this_number->get_digit(b);
        char digit = actual->get_data() - '0' - carry;
        if (digit < 0)
        {
            digit = 10 + digit;
            carry = 1;
        }
        else carry = 0;

        actual->set_data(digit + '0');
        if (b) b--;
        else break;
    }

    // here b == 0. we delete 0
    while (this_number->get_number()->get_data() == '0')
        if(false == this_number->remove_symbol(0))
            error_handeler("operator- failed");

    return *this_number;
}

const natural_number& natural_number::operator - (const basic_number& nr)
{
    // operator +
    if (nr.get_number()->get_data() == '-')
        return *this + *(new natural_number(nr));

    // nr greater than this->number
    if (nr.get_digits() > this->get_digits())
        return *(new natural_number);

    // delete floating points
    natural_number integer = nr;

    // subtraction with a natural number
    natural_number* this_number = new natural_number(*this);
    ull b = this->bytes - 1, b_nr = nr.get_digits() - 1;
    char carry = 0;
    bool flag = true;

    while (integer.get_number()->get_data() != '0')
    {
        digit_node* actual = this_number->get_digit(b);
        char digit = (actual->get_data() - '0') - (integer.get_digit(b_nr)->get_data() - '0') - carry;
        if (digit < 0)
        {
            digit = 10 + digit;
            carry = 1;
        }
        else carry = 0;

        actual->set_data(digit + '0');

        if (b && integer.get_digit(0)->get_data() != '0') b--;
        else flag == false;
    }

    if (carry && b == 0 && integer.get_number()->get_data() == '0') // equivalent to carry && b == 0
        return *(new natural_number);
    if (flag == false) b--;
    while (carry) // here integer is consumed, we only solve the carry problem here
    {
        digit_node* actual = this_number->get_digit(b);
        char digit = actual->get_data() - '0' - carry;
        if (digit < 0)
        {
            digit = 10 + digit;
            carry = 1;
        }
        else carry = 0;

        actual->set_data(digit + '0');
        if (b) b--;
        else break;
    }

    // here b == 0. we delete 0
    while (this_number->get_number()->get_data() == '0')
        if (false == this_number->remove_symbol(0))
            error_handeler("operator- failed");

    return *this_number;
}

const natural_number& natural_number::operator * (const float& nr)
{
    int n = abs((int)cast_float(nr));
    natural_number copy(*this), * this_number = new natural_number(*this);
    for (int i = 0; i < n; i++)
        *this_number = *this_number + copy;
    
    return *this_number;
}

const natural_number& natural_number::operator * (const basic_number& nr)
{
    if (nr.get_number()->get_data() == '0')
        reinitialise(number);

    natural_number copy(*this), * this_number = new natural_number(*this);
    natural_number it, n(nr);
    while ((it == n) == false)
    {
        float one = 1.0f;
        *this_number = *this_number + copy;
        it + one;
    }

    return *this;
}

const natural_number& natural_number::operator / (const float& nr)
{
    int quotient = 0;
    natural_number* this_number = new natural_number(*this);

    while (this_number->get_number()->get_data() != '0')
    {
        *this_number = *this_number - nr;
        quotient++;
    }

    return *(new natural_number(quotient));
}

const natural_number& natural_number::operator / (const basic_number& nr)
{
    int quotient = 0;
    natural_number* this_number = new natural_number(*this);

    while (this_number->get_number()->get_data() != '0')
    {
        *this_number = *this_number - nr;
        quotient++;
    }

    return *(new natural_number(quotient));
}

bool natural_number::operator == (const float& nr)
{
    if (nr < 0 || nr != abs((int)nr))
        return false;

    int integer = (int)nr;
    if (this->bytes != digits_number(integer))
        return false;

    int power = 1;
    while (power * 10 <= integer)
        power *= 10;

    digit_node* it = number;
    while (integer && it)
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

bool natural_number::operator == (const basic_number& nr)
{
    if (this->bytes != nr.get_bytes() || nr.get_number()->get_data() == '-')
        return false;

    digit_node* it = number, * it_nr = nr.get_number();
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

ull natural_number::get_digits() const
{
    return this->bytes;
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

// extra:
float cast_float(float nr)
{
    char digit = (int)(nr * 10) % 10;
    if (digit >= 5)
        return nr + 1;
    return nr;
}