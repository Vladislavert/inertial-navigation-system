/* ************************************ */
/* 	|Author: Vladislavert              |*/
/* 	|e-mail: chuvarevanv@gmail.ru      |*/
/* 	|ahrs.cpp                          |*/
/*	|__________________________________|*/
/* ************************************ */

#include "ahrs.hpp"

/**
 * @brief расчёт ориентации
 * 
 * @param initOrientation начальное значение ориентации
 * @param dataIMU данные с БИНС(акселерометр(X, Y, Z), гироскоп(X, Y, Z), магнетометр(X, Y))
 * @param dataTime время с начала замера данных с датчиков
 * @return ориентация(тангаж, крен, рысканье)
 */
vectDouble2d_t	getOrientation(const vectDouble_t& initOrientation, const vectDouble2d_t& dataIMU, const vectDouble_t& dataTime)
{
	vectDouble2d_t	resOrientation; // углы ориентации(тангаж, крен, рысканье)
	vectDouble_t	dataAccelerometer; // данные с акселерометра
	vectDouble_t	dataGyroscopePast; // данные с гироскопа на предыдущем шаге
	vectDouble_t	dataGyroscopeCurrent; // данные с гироскопа на нынешнем шаге
	vectDouble_t	dataMagnetometer; // данные с магнетометра
	vectDouble_t	angleAccelerometer; // углы, получаемые с акселерометра
	vectDouble_t	angleGyroscope; // углы получаемы с гироскопа
	vectDouble_t	angleMagnetometer; // углы получаемые с магнитометра

	for (unsigned int j = 0; j < quantityAxes; j++)
	{
		dataAccelerometer.push_back(dataIMU[0][j]);
		if (j < quantityAxes - 1)
		{
			dataGyroscopePast.push_back(dataIMU[0][j + 3]);
			dataMagnetometer.push_back(dataIMU[0][j + 6]);
		}
	}
	dataGyroscopePast.push_back(initOrientation[2]);
	resOrientation.push_back(dataGyroscopePast);
	angleAccelerometer = getAngleAccelerometer(dataAccelerometer);
	for	(unsigned int i = 1; i < dataIMU.size() - 1; i++)
	{
		dataAccelerometer.clear();
		dataMagnetometer.clear();
		for (unsigned int j = 0; j < quantityAxes; j++)
		{
			dataAccelerometer.push_back(dataIMU[i][j + indxAcc]);
			dataGyroscopePast.push_back(dataIMU[i][j + indxGyro]);
			dataGyroscopeCurrent.push_back(dataIMU[i][j + indxGyro]);
			if (j < quantityAxes - 1)
				dataMagnetometer.push_back(dataIMU[i][j + indxMagnet]);
		}
		angleAccelerometer = getAngleAccelerometer(dataAccelerometer);
		angleMagnetometer = getAngleMagnetometer(dataMagnetometer);
		angleGyroscope = getAngleGyroscope((resOrientation[i - 1]),
										   dataGyroscopeCurrent, dataTime[i] - dataTime[i - 1]);
		resOrientation.push_back(complementaryFilter(angleAccelerometer , angleGyroscope,
													 angleMagnetometer));
		dataGyroscopeCurrent.clear();
		angleAccelerometer.clear();
		angleMagnetometer.clear(); 
		angleGyroscope.clear();

	}
	return (resOrientation);
}

/**
 * @brief вычисление углов ориентации на основе данных с акселерометра
 * 
 * @param dataAccelerometer данные с акселерометра(кажущееся ускорение по связанным осям)
 * @return углы ориентации(тангаж, крен)
 */
vectDouble_t	getAngleAccelerometer(const vectDouble_t& dataAccelerometer)
{
	vectDouble_t	angleAccelerometer;

	for (unsigned int i = 0; i < quantityAxes - 1; i++)
		angleAccelerometer.push_back(std::atan2(dataAccelerometer[i], dataAccelerometer[2]));
	return (angleAccelerometer);
}

/**
 * @brief вычисление углов ориентации на основе данных с гироскопа
 * 
 * @param dataGyroscopePast данные с гироскопа(угловая скорость вращения по трём связанным осям) на предыдущем шаге
 * @param dataGyroscopeFuture данные с гироскопа(угловая скорость вращения по трём связанным осям) на текущем шаге
 * @param time шаг между замерами
 * @return углы ориентации(тангажа, крен, рысканье) 
 */
vectDouble_t	getAngleGyroscope(const vectDouble_t& dataGyroscopePast, const vectDouble_t& dataGyroscopeCurrent, const double dt)
{
	vectDouble_t	angleGyroscope;

	for (unsigned int i = 0; i < quantityAxes - 1; i++)
		angleGyroscope.push_back(integralEuler(dataGyroscopePast[i], dataGyroscopeCurrent[i], dt));
	angleGyroscope.push_back(absRad(integralEuler(dataGyroscopePast[2], dataGyroscopeCurrent[2], dt)));
	return(angleGyroscope);
}

/**
 * @brief вычисление углов ориентации на основе данных с магнитометра
 * 
 * @param dataMagnetometer данные с магнитометра(измерения по осям X, Y)
 * @return рысканье
 */
vectDouble_t	getAngleMagnetometer(const vectDouble_t& dataMagnetometer)
{
	vectDouble_t	angleMagnetometer;

	angleMagnetometer.push_back(absRad(-std::atan2(dataMagnetometer[0], dataMagnetometer[1])));
	return(angleMagnetometer);
}

/**
 * @brief перевод в диапазон от 0 до 2*pi 
 * 
 * @param rad значение в радианах(от 0 до pi/-pi)
 * @return значение в радианах(от 0 до 2*pi)
 */
double	absRad(double rad)
{
	if (rad < 0)
		return(M_PI + (M_PI + rad));
	else if (rad > 2*M_PI)
		return (rad - 2*M_PI);
	else
		return (rad);
}
