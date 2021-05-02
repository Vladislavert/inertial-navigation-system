#include "ahrs.hpp"

/**
 * @brief вычисление углов ориентации на основе данных с акселерометра
 * 
 * @param dataAccelerometer данные с акселерометра(кажущееся ускорение по связанным осям)
 * @return углы ориентации(тангаж, крен)
 */
double	*getAngleFromAccelerometer(const double dataAccelerometer[3])
{
	double *angleAccelerometer;

	angleAccelerometer = new double[2];
	for (unsigned int i = 0; i < 2; i++)
		angleAccelerometer[i] = std::atan2(dataAccelerometer[i], dataAccelerometer[2]);
	return (angleAccelerometer);
}

/**
 * @brief вычисление углов ориентации на основе данных с гироскопа
 * 
 * @param dataGyroscopePast данные с гироскопа(угловая скорость вращения по трём связанным осям) на предыдущем шаге
 * @param dataGyroscopeFuture данные с гироскопа(угловая скорость вращения по трём связанным осям) на текущем шаге
 * @param time шаг между замерами
 * @return углы ориентации(тангжа, крен, рысканье) 
 */
double	*getAngleGyroscope(const double dataGyroscopePast[3], const double dataGyroscopeCurrent[3], const double dt)
{
	double *angleGyroscope;

	angleGyroscope = new double[3];
	for (unsigned int i = 0; i < 3; i++)
		angleGyroscope[i] = integralEuler(dataGyroscopePast[i], dataGyroscopeCurrent[i], dt);
	return(angleGyroscope);
}

/**
 * @brief вычисление углов ориентации на основе данных с магнитометра
 * 
 * @param dataMagnetometer данные с магнитометра(измерения по осям X, Y)
 * @return рысканье
 */
double	*getAngleMagnetometer(const double dataMagnetometer[2])
{
	double *angleMagnetometr;

	angleMagnetometr = new double[1];
	angleMagnetometr[0] = std::atan2(dataMagnetometer[0], dataMagnetometer[1]);
	if (angleMagnetometr[0] > 0)
		angleMagnetometr[0] = (M_PI + (M_PI + angleMagnetometr[0])) * M_PI;
	return(angleMagnetometr);
}

