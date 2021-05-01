#include "calcProbabilityCharact.hpp"

/*
	расчёт математического ожидания дискретной СВ
*/
double	meanCalculate(const Vec &dataArray)
{
	double mean;

	for (size_t i = 0; i < dataArray.size(); i++)
		mean += dataArray[i];
	mean /= dataArray.size();
	return (mean);
}

/*
	расчёт дисперсии дискретной СВ
*/
double	dispersionCalculate(const Vec &dataArray, const double &mean)
{
	double dispersion;

	for (size_t i = 0; i < dataArray.size(); i++)
		dispersion += squaring(dataArray[i] - mean);
	dispersion /= dataArray.size();
	return (dispersion);
}