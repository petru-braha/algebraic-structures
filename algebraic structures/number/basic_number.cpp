#include "basic_number.h"

bool basic_number::insert_digit(const char& digit)
{
    if (number == nullptr)
    {
        number = new digit_node(digit);
        return true;
    }

    digit_node* it = number;
    while (it->)
    {
        if (it->get_data == key)
        {
            if (value)
                it->add_value(value);
            return it;
        }

        entry* nxt = it->next_key;
        if (nxt->key_name == NULL)
        {
            delete nxt;
            it->next_key = new entry(key, value);
            nxt = it->next_key;
            nxt->next_key = new entry(NULL, NULL);
            return nxt;
        }
        it = it->next_key;
    }
    return nullptr;

}

bool basic_number::remove_digit(const char& digit)
{

}

//-------------------------------------------------------------------------------------------

/*


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



/*

Map<K, V>::pointer_entry Map<K, V>::add_key(const K& key, const V& value)
{
    if (this->first_key == nullptr)
    {
        this->first_key = new entry(key, value);
        this->first_key->next_key = new entry(NULL, NULL);
        return this->first_key;
    }

    entry* it = this->first_key;
    while (it)
    {
        if (it->key_name == key)
        {
            if(value)
                it->add_value(value);
            return it;
        }

        entry* nxt = it->next_key;
        if (nxt->key_name == NULL)
        {
            delete nxt;
            it->next_key = new entry(key, value);
            nxt = it->next_key;
            nxt->next_key = new entry(NULL, NULL);
            return nxt;
        }
        it = it->next_key;
    }
    return nullptr;
}



template <class K, class V>
bool Map<K, V>::Delete(const K& key)
{
    if (this->first_key == nullptr)
        return false;

    entry* it = this->first_key, * nxt = it->next_key;
    if (it->key_name == key)
    {
        this->first_key = nxt;
        delete it;
        return true;
    }
    while (nxt)
    {
        if (nxt->key_name == key)
        {
            entry* temp = nxt;
            nxt = nxt->next_key;
            it->next_key = nxt;
            delete temp;
            return true;
        }

        it = nxt;
        nxt->next_key;
    }
    return false;
}

*/