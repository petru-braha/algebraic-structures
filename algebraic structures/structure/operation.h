#pragma once
#include "../number/basic_number.h"

template <class v = basic_number>
class operation // binary operation, unary inverse function, if there is no neutral element 
{
	typedef v& (*f)(const v&, const v&), fct;
	typedef v& (*i)(const v&), inv;
protected:
	const v& (*function)(const v& x, const v& y);
	const v& (*inversef)(const v& x);
	v* neutral_element;
public:
	operation();
	operation(fct);
	operation(fct, inv);
	operation(fct, inv, const v& nr);
	
	const operation& operator = (const operation& op);

	bool discover_inverse();
	bool discover_neutral();
	fct get_function();
	inv get_inversef();

	~operation();
};