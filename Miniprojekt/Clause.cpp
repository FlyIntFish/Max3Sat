#include "Clause.h"

std::ostream& operator<<(std::ostream& stream, const Clause& c)
{
	for (int i = 0; i < 3; i++)
	{
		if (!c.positive[i])
			stream << '-';
		stream << c.val[i] << " ";
	}
	return stream;
}

bool Clause::check(bool val1, bool val2, bool val3)
{
	return ((!(val1 ^ firstPositive)) || (!(val2 ^ secondPositive)) || (!(val3 ^ thirdPositive)));
}
