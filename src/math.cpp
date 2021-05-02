#include "math.hpp"

/**
 * @brief возведение в квадрат
 * 
 * @param argument аргумент, который возводят в квадрат
 * @return значение аргумента в квадрате
 */
double	squaring(const double &argument)
{
	return (argument * argument);
}

/**
 * @brief интегрирование методом Эйлера
 * 
 * @param time элемент интегрирования
 * @param data аргумент, который интегрируется
 * @return проинтегрированные значения
 */
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

/**
 * @brief интегррирование методом Эйлера
 * 
 * @param dataPast значение на предыдущем шаге
 * @param dataCurrent значение на текущем шаге
 * @param dt шаг интегрирования
 * @return проинтегрпированное значение
 */
double	integralEuler(const double dataPast, const double dataCurrent, double dt)
{
	double result;

	result = dataPast + dataCurrent * dt;
	return (result);
}