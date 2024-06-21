#include <stdio.h>
#include <stdlib.h>
#include "natural_number.h"

digit_node* null = nullptr;

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
        add_beginng(null, number, last_digit(integer));
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
    int integer = abs(int(nr));
    while (integer)
    {
        add_beginng(null, number, last_digit(integer));
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
        add_beginng(null, number, '1');
    return *this;
}

//basic_number& natural_number::operator - (const float& nr);
//basic_number& natural_number::operator - (const basic_number* nr);
/*/
basic_number& operator * (const float& nr);
basic_number& operator * (const basic_number* nr);
basic_number& operator / (const float& nr);
basic_number& operator / (const basic_number* nr);

bool operator == (const float& nr);
bool operator == (basic_number* nr);

basic_number& operator += (const float& nr);
basic_number& operator += (basic_number* nr);
basic_number& operator -= (const float& nr);
basic_number& operator -= (basic_number* nr);

basic_number& operator *= (const float& nr);
basic_number& operator *= (basic_number* nr);
basic_number& operator /= (const float& nr);
basic_number& operator /= (basic_number* nr);
*/


//---------------------------------------------------------------------------------------------------
// constant functions:


/*
basic_number& basic_number::operator *= (int nr)
{
    vector<int> copy;
    copy_vector(copy, this->number);
    while (nr > 1) // add to this->number copy for nr times
    {
        bool condition = false; // addition of units exceded 9
        int index_copy = copy.size() - 1, i = 0;
        for (i = this->number.size() - 1; i >= 0 && index_copy >= 0; i--, index_copy--)
        {
            if (condition) // the previous addition was over 9
            {
                if (!(this->number[i] + copy[index_copy] + 1 > 9))
                    condition = false;
                this->number[i] = (this->number[i] + 1) % 10;
            }

            else if (this->number[i] + copy[index_copy] > 9) condition = true;

            //add
            this->number[i] = (this->number[i] + copy[index_copy]) % 10;
        }

        if (condition)
        {
            while (i >= 0 && this->number[i] == 9)
            {
                this->number[i] = 0;
                i--; // can be -1
            }

            if (i >= 0)
                this->number[i]++;
            else
                this->number.insert(this->number.begin(), 1);
        }

        nr--;
    }

    return *this;
}
*/
