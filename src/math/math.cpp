/* ************************************ */
/* 	|Author: Vladislavert              |*/
/* 	|e-mail: chuvarevanv@gmail.ru      |*/
/* 	|math.cpp                          |*/
/*	|__________________________________|*/
/* ************************************ */

#include "math.hpp"

/**
 * @brief перевод из градусов в радианы
 * 
 * @param deg градусы
 * @return радианы
 */
double			degToRad(double deg)
{
	double	rad;

	rad = (PI/180) * deg;
	return (rad);
}

/**
 * @brief перевод из радиан в градусы
 * 
 * @param rad радианы
 * @return градусы
 */
double			radToDeg(double rad)
{
	double deg;

	deg = (180/PI) * rad;
	return (deg);
}
/**
 * @brief возведение в квадрат
 * 
 * @param argument аргумент, который возводят в квадрат
 * @return значение аргумента в квадрате
 */
double	squaring(double argument)
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
vectDouble_t	integralEuler(const vectDouble_t& time, const vectDouble_t& data, double initialData)
{
	vectDouble_t	result(time.size());

	result[0] = initialData + data[0] * (time[1] - time[0]);
	for (size_t i = 1; i < time.size() - 1; i++)
	{
		result[i] += result[i - 1] + (data[i] * (time[i + 1] - time[i]));
	}
	return (result);
}

/**
 * @brief интегрирование методом Эйлера
 * 
 * @param dataPast значение на предыдущем шаге
 * @param dataCurrent значение на текущем шаге
 * @param dt шаг интегрирования
 * @return проинтегрированное значение
 */
double			integralEuler(const double dataPast, const double dataCurrent, double dt)
{
	double result;

	result = dataPast + dataCurrent * dt;
	return (result);
}