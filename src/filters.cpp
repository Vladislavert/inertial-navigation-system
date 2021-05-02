#include "filters.hpp"

/**
 * @brief фильтр нижних частот(ФНЧ)
 * 
 * @param input входные данные
 * @param time время
 * @param T постоянная времени
 * @return отфильтрованные данные
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

/**
 * @brief фильтр верхних частот(ФВЧ)
 * 
 * @param input входные данные 
 * @param time время
 * @param T постоянная времени
 * @return отфильтрованные даннные
 */
Vec		HighPassFilter(Vec input, Vec time, double T)
{
	Vec output(input.size());

	return (output);
}

/**
 * @brief комплементарный фильтр
 * 
 * @param angleAccelerometer данные об углах полученные с акселерометра
 * @param angleGyroscope данные об углах полученные с гироскопа
 * @param angleMagnetometer данные об углах полученные с магнитометра
 * @return значение оценки ориентации(тангаж, крен, рысканье)
 */
double	*complementaryFilter(double *angleAccelerometer, double *angleGyroscope, double *angleMagnetometer)
{
	double *orientation;

	return (orientation);
}