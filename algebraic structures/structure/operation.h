#pragma once
#include "../number/basic_number.h"

class operation // binary operation, unary inverse function, if there is no neutral element 
{
	basic_number& (*function)(const basic_number& x, const basic_number& y);
	basic_number& (*inversef)(const basic_number& x);
	basic_number* neutral_element;
public:

	typedef basic_number& (*f)(const basic_number&, const basic_number&), fct;
	typedef basic_number& (*i)(const basic_number&), inv;

	operation();
	operation(fct);
	operation(fct, inv);
	operation(fct, inv, const basic_number& nr);
	
	operation& operator = (const operation& op);

	bool discover_inverse();
	bool discover_neutral();
	fct get_function();
	inv get_inversef();

	~operation();
};