/*
#include "basic_number.h"


//digit on index!
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

void basic_number::print() const
{
    for (int i = 0; i < this->number.size(); i++)
        std::cout << this->number[i];
}

*/