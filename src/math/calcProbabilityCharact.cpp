/* ************************************ */
/* 	|Author: Vladislavert              |*/
/* 	|e-mail: chuvarevanv@gmail.ru      |*/
/* 	|calcProbabilityCharact.cpp        |*/
/*	|__________________________________|*/
/* ************************************ */

#include "calcProbabilityCharact.hpp"

/**
 * @brief расчёт математического ожидания дискретной случайной величины(СВ)
 * 
 * @param dataArray массив измерений
 * @return математическое ожидание СВ
 */
double	meanCalculate(const vectDouble_t &dataArray)
{
	double mean;

	for (size_t i = 0; i < dataArray.size(); i++)
		mean += dataArray[i];
	mean /= dataArray.size();
	return (mean);
}

/**
 * @brief расчёт дисперсии дискретной случайной величины(СВ)
 * 
 * @param dataArray массив измерений
 * @param mean математическое ожидание
 * @return дисперсия СВ
 */
double	dispersionCalculate(const vectDouble_t &dataArray, const double &mean)
{
	double dispersion;

	for (size_t i = 0; i < dataArray.size(); i++)
		dispersion += squaring(dataArray[i] - mean);
	dispersion /= dataArray.size();
	return (dispersion);
}