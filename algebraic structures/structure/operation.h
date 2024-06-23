#pragma once
#include "../number/basic_number.h"

class operation
{
	basic_number& (*function)(const basic_number& x, const basic_number& y);
	basic_number& (*inversef)(const basic_number& x);
	basic_number* neutral_element;
public:
	bool closure();

};