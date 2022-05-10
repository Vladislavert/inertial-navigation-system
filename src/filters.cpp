/* ************************************ */
/* 	|Author: Vladislavert              |*/
/* 	|e-mail: chuvarevanv@gmail.ru      |*/
/* 	|filters.cpp                       |*/
/*	|__________________________________|*/
/* ************************************ */

#include "filters.hpp"

/**
 * @brief фильтр нижних частот(ФНЧ)
 * 
 * @param input входные данные для фильтрации
 * @param time время
 * @param T постоянная времени
 */
void			lowPassFilter(vectDouble_t& input, const vectDouble_t& time, const double T)
{
	double alpha;
	double dt;
	
	dt = time[1] - time[0];
	alpha = dt/(T + dt);
	input[0] = alpha * input[0];
	for	(size_t i = 1; i < input.size() - 1; i++)
	{
		dt = time[i + 1] - time[i];
		alpha = dt/(T + dt);
		input[i] = alpha * input[i] + (1 - alpha) * input[i - 1];
	}
}

/**
 * @brief фильтр верхних частот(ФВЧ)
 * 
 * @param input входные данные 
 * @param time время
 * @param T постоянная времени
 * @return отфильтрованные данные
 */
// vectDouble_t	highPassFilter(const vectDouble_t *input, const vectDouble_t *time, const double T)
// {
// 	vectDouble_t output((*input).size());

// 	return (output);
// }

/**
 * @brief комплементарный фильтр
 * 
 * @param angleAccelerometer данные об углах полученные с акселерометра
 * @param angleGyroscope данные об углах полученные с гироскопа
 * @param angleMagnetometer данные об углах полученные с магнитометра
 * @return значение оценки ориентации(тангаж, крен, рысканье)
 */
vectDouble_t	complementaryFilter(const vectDouble_t& angleAccelerometer, const vectDouble_t& angleGyroscope, const vectDouble_t& angleMagnetometer)
{
	vectDouble_t orientation;
	double		wGyroscope = 0.98;
	double		wAccelerometer = 1 - wGyroscope;
	double		wMagnetometer = 1 - wGyroscope;

	orientation.push_back(wAccelerometer * angleAccelerometer[0] + wGyroscope * angleGyroscope[0]);
	orientation.push_back(wAccelerometer * angleAccelerometer[1] + wGyroscope * angleGyroscope[1]);
	orientation.push_back(wMagnetometer * angleMagnetometer[0] + wGyroscope * angleGyroscope[2]);

	return (orientation);
}