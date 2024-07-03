#pragma once
#include "../number/basic_number.h"

template <class v = basic_number>
class finite_set
{
protected:
	v* elements;
	ull n;
public:
	finite_set();
	finite_set(const ull& n);
	finite_set(v* values, const ull& n);

	finite_set(const finite_set& set);
	finite_set(const finite_set&& set);

	void operator = (const finite_set& set);

	void insert_element(const v*& value);
	void insert_element(const v*& value, const ull& index);
	void remove_element(const v*& value);

	const basic_number& operator [] (const ull& index) const;
	const basic_number& get_psition (const v& value) const;
	
	void delete_same();
	void sort();

	// algebraic function
	operator char() const; // return how many divisors of 0 are there
	ull  get_size() const;

	~finite_set();
};

template <class v = basic_number>
finite_set<v> reunion(const finite_set<v>& set1, const finite_set<v>& set2);

template <class v = basic_number>
finite_set<v> intersection(const finite_set<v>& set1, const finite_set<v>& set2);