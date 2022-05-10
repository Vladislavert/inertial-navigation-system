/* ************************************ */
/* 	|Author: Vladislavert              |*/
/* 	|e-mail: chuvarevanv@gmail.ru      |*/
/* 	|initialExhibition.cpp             |*/
/*	|__________________________________|*/
/* ************************************ */

#include "initialExhibition.hpp"

/**
 * @brief Корректирует данные с учётом математического ожидание и дисперсии
 * 
 * @param dataIMU данные с БИНС(акселерометр(X, Y, Z), гироскоп(X, Y, Z), магнетометр(X, Y))
 * @param dataInitIMU данные с БИНС(акселерометр(X, Y, Z), гироскоп(X, Y, Z), магнетометр(X, Y)) для начальной выставки
 * @param g ускорение свободного падения во время начальной выставки
 */
void	getCorrectData(vectDouble2d_t& dataIMU, const vectDouble2d_t& dataInitIMU, const double g)
{
	vectDouble2d_t 		dataIMUTranspose(dataInitIMU[0].size()); // данные с БИНС(акселерометр(X, Y, Z), гироскоп(X, Y, Z), магнетометр(X, Y))
	double				*meanAcc; // математическое ожидание акселерометра по трём связанным осям
	double				*dispersionAcc; // дисперсия данных с акселерометра по трём связанным осям
	double				*threeCovAcc; // 3*sigma акселерометра по трём связанным осям
	double				*meanGyro; // математическое ожидание гироскопа по трём связанным осям
	double				*dispersionGyro; // дисперсия данных с гироскопа по трём связанным осям
	double				*threeCovGyro; // 3*sigma гироскопа по трём связанным осям
	double				valueInit; // Значение, которое присваивается при попадания в "мёртвую" зону 

	meanAcc = new double[quantityAxes];
	dispersionAcc = new double[quantityAxes];
	threeCovAcc = new double[quantityAxes];
	meanGyro = new double[quantityAxes];
	dispersionGyro = new double[quantityAxes];
	threeCovGyro = new double[quantityAxes];
	for	(unsigned int i = 0; i < dataInitIMU[0].size(); i++)
		for (const auto & j : dataInitIMU)
			dataIMUTranspose[i].push_back(j[i]);
	for	(unsigned int i = 0; i < quantityAxes; i++)
		meanAcc[i] = meanCalculate(dataIMUTranspose[indxAcc + i]);
	for	(unsigned int i = 0; i < quantityAxes; i++)
		meanGyro[i] = meanCalculate(dataIMUTranspose[indxGyro + i]);
	for	(unsigned int i = 0; i < quantityAxes; i++)
	{
		dispersionAcc[i] = dispersionCalculate(dataIMUTranspose[indxAcc + i], meanAcc[i]);
		dispersionGyro[i] = dispersionCalculate(dataIMUTranspose[indxGyro + i], meanGyro[i]);
	}
	for (unsigned int i = 0; i < quantityAxes; i++)
	{
		threeCovAcc[i] = 3 * sqrt(dispersionAcc[i]);
		threeCovGyro[i] = 3 * sqrt(dispersionGyro[i]);
	}
	for (auto & measurement : dataIMU)
		for (unsigned int j = 0; j < quantityAxes; j++)
		{
			if (j == quantityAxes - 1)
			{
				measurement[indxAcc + j] = measurement[indxAcc + j] - (meanAcc[j] - g);
				valueInit = g;
			}
			else
			{
				measurement[indxAcc + j] = measurement[indxAcc + j] - meanAcc[j];
				valueInit = 0;
			}
			measurement[indxGyro + j] = measurement[indxGyro + j] - meanGyro[j];
			if (measurement[indxAcc + j] < (threeCovAcc[j] + valueInit) && measurement[indxAcc + j] > (-threeCovAcc[j] + valueInit))
				measurement[indxAcc + j] = valueInit;
			if (measurement[indxGyro + j] < (threeCovGyro[j] + valueInit) && measurement[indxGyro + j] > (-threeCovGyro[j] + valueInit))
				measurement[indxGyro + j] = valueInit;
		}
	delete[] meanAcc;
	delete[] dispersionAcc;
	delete[] threeCovAcc;
	delete[] meanGyro;
	delete[] dispersionGyro;
	delete[] threeCovGyro;
}

/**
 * @brief накопление позиции по ГНСС
 * 
 * @param dataInitGNSS данные с ГНСС приёмника
 * @return среднее значение широты, долготы, высоты
 */
double	*accumulationPositionGNSS(const vectDouble2d_t& dataInitGNSS)
{
	double *meanResult;

	meanResult = new double[3];
	for (auto & measurementGnss : dataInitGNSS)
	{
		meanResult[0] += measurementGnss[0];
		meanResult[1] += measurementGnss[1];
		meanResult[2] += measurementGnss[2];
	}
	meanResult[0] /= dataInitGNSS.size();
	meanResult[1] /= dataInitGNSS.size();
	meanResult[2] /= dataInitGNSS.size();
	return (meanResult);
}
