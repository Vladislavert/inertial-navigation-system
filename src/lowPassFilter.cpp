#include "lowPassFilter.hpp"

/*
	фильтр низких частот

	input	- входные данные
	dt		- шаг
	T		- постоянная времени
*/
Vec	lowPassFilter(Vec input, Vec time, double T)
{
	Vec output(input.size());
	double alpha;
	double dt;
	
	dt = time[1] - time[0];
	alpha = dt/(T + dt);
	output[0] = alpha * input[0];
	for	(size_t i = 1; i < input.size() - 1; i++)
	{
		dt = time[i + 1] - time[i];
		alpha = dt/(T + dt);
		output[i] = alpha * input[i] + (1 - alpha) * output[i - 1];
	}
	return (output);
}