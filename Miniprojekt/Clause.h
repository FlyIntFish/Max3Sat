#pragma once
#include "Constants.h"

struct Clause
{
	Integer val[3];
	bool positive[3];
	Clause() = default;
	Clause(Integer first_, bool positive1, Integer second_, bool positive2, Integer third_, bool positive3) : val{first_, second_, third_},
	positive{positive1, positive2, positive3}{}
	bool check(bool val1, bool val2, bool val3) const;
};

std::ostream& operator<<(std::ostream& stream, const Clause& c);