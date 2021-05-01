#include "math.hpp"

double	squaring(const double &argument)
{
	return (argument * argument);
}

Vec		integralEuler(Vec time, Vec data)
{
	Vec result(time.size());

	result[0] = data[0] * (time[1] - time[0]);
	for (size_t i = 1; i < time.size() - 1; i++)
	{
		result[i] += result[i - 1] + (data[i] * (time[i + 1] - time[i]));
	}
	return (result);
}