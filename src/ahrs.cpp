#include "ahrs.hpp"

/**
 * @brief вычисление углов ориентации на основе данных с акселерометра
 * 
 * @param dataAccelerometer - данные с акселерометра(кажущееся ускорение по связанным осям)
 * @return углы ориентации(тангаж, крен)
 */
double	*getAngleFromAccelerometer(double *dataAccelerometer)
{
	double *angleFromAccelerometer;

	angleFromAccelerometer[0] = std::atan2(dataAccelerometer[0], dataAccelerometer[2]);
	angleFromAccelerometer[1] = std::atan2(dataAccelerometer[1], dataAccelerometer[2]);
	return (angleFromAccelerometer);
}

/**
 * @brief вычисление углов ориентации на основе данных с гироскопа
 * 
 * @param dataGyroscope - данные с гироскопа()
 * @return углы ориентации()
 */
double	*getAngleGyroscope(const double *dataGyroscope)
{
	double *angleGyroscope;

	return(angleGyroscope);
}

/**
 * @brief вычисление углов ориентации на основе данных с магнитометра
 * 
 * @param dataMagnetometer - данные с магнитометра()
 * @return углы ориентации()
 */
double	*getMagnetometer(const double *dataMagnetometer)
{
	double *angleMagnetometr;

	return(angleMagnetometr);
}

