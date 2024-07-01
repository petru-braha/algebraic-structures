#pragma once
#include "digit_node.h"
#define KB (ull)1000
#define MB (ull)(1000 * KB)
#define GB (ull)(1000 * MB)
#define max_bytes (ull)(GB + GB + GB)

#define error_handeler(msg)\
{ printf("error: %s.\n", msg); return(-1); }

class basic_number // the most general number, abstract class => complex
{
    typedef const basic_number& b_nr;
protected:
    digit_node* number = nullptr;  // root of the linked list. list goes from right to left
    ull bytes;

    // at the end 
    digit_node* insert_symbol(const char& symbol); // returns the previous before the added one
    digit_node* insert_symbol(digit_node* previous, const char& symbol); // returns thr added one AND override the allocated memory
    bool        remove_symbol();

public:
    basic_number();
    basic_number(float nr);   
    basic_number(float nr0, float nr1);

    basic_number(const char* buffer); // the actual big numbers will be placed with this function
    basic_number(const char* buffer0, const char* buffer1);

    basic_number(const basic_number& nr);
    basic_number(const basic_number&& nr) noexcept;

    // pure functions
    virtual b_nr operator + (const float& nr) = 0;
    virtual b_nr operator + (const basic_number& nr) = 0;
    virtual b_nr operator - (const float& nr) = 0;
    virtual b_nr operator - (const basic_number& nr) = 0;

    virtual b_nr operator * (const float& nr) = 0;
    virtual b_nr operator * (const basic_number& nr) = 0;
    virtual b_nr operator / (const float& nr) = 0;
    virtual b_nr operator / (const basic_number& nr) = 0;

    //virtual bool operator > (const float& nr) = 0;
    //virtual bool operator > (const basic_number* nr) = 0;

    virtual bool operator == (const float& nr) = 0;
    virtual bool operator == (const basic_number& nr) = 0;


    // if possible (small enough) else returns -1
    virtual operator int() const;
    virtual operator float() const;

    digit_node* get_digit(ull i) const;
    digit_node* get_number() const;
    ull         get_bytes () const;
    virtual void print() const = 0;
};

int concatenation(digit_node*& ptr, const char& symbol, ull& bytes);

char last_digit(int& nr);
void add_beginng(digit_node*& ptr, const char& symbol);
void add_beginng(digit_node*& previous, digit_node*& ptr, const char& symbol);
int  add_between(digit_node*& ptr1, digit_node* ptr2, const int& symbol);

const char* convert_float(float nr);
inline int digits_number(ull nr);
inline int bytes_number(float nr);
void reinitialise(digit_node*& root);
int  cast_float(float nr);
