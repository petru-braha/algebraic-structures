#pragma once
#include "../number/types/natural_number.h" // these are types for the template
#include "../number/types/integer.h"
#include "../number/types/rational_number.h"
#include "../number/types/real_number.h"
#include "../number/types/complex_number.h"

template <class T = int, ull capacity = 0>
struct finite_set
{
	T set[capacity];
};