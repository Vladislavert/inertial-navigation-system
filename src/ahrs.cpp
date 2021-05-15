/* *************************************************************************************************** */
/* 	|Author: Vladislavert         |ssssssssssssssso++——+++osssssssssssssssssssssssssssssssssssssssss|  */
/* 	|e-mail: chuvarevan@mail.ru   |yyyysoooooo..   /   |    ./yyyyyyyyyyosshhhhhyyyyyyyyyyyyyyyyyyyy|  */
/* 	|_____________________________|yyyyyyysssso////  /syyyyyyyyyyyyyyy0    /yhhhhhyyyyyyyyyyyyyyyyyy|  */
/*	|ssysyyyyysssyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyso+   /ssyyyyyyyyyyyyso    0yhhhhhhhhyhyyyyyyyyyyyyyy|  */
/*	|syyyyyys+.     ++osy      ...sssoosssssssoo+ +o/osssyyyyso+//s/ /oyyyhyhhhhhhhyyyyyyyyyyyyyyyyy|  */
/*	|syyyyyysooo+/::/+/  ++++oooo+++ooooosssssshhyyyyyooo+//+oo++/ /:os+++++++++++++yyhhhyyyyyyyyyyy|  */
/*	|ssssyyyyyys+/    ///////yyyyyys:--::/syo+//:/::::::/ooo+///  /oys\.          /ossyyyyyyyyyy'sss|  */
/*	|yyyyyysyys/    ::://///////::/:------+s/::----::::::::/:-//+osssyyyyyyyss+/::://o ..........+ss|  */
/*	|syyyyyyyso/   :ooooooooo---/-----::---:::----::::--:/----://+oooossyyhhhhhy/::::  :oyyyyyyyyyyy|  */
/*	|yyysyyyyso+ +++/:ooooooo--/-0----/-/-----::::::::.-::::----+/:::::///++++++|     ////shhhhyyyyy|  */
/*	|ysyyyyyysssossss+/:+oooo:|-00---/-0-..-----.-:---.-------::: ++++++++++//:::/   //::/oyhyyyyyyy|  */
/*	|syyyyyysssssyyyo+/osssss+-\-0-:|-00.....--...-//:.----::      ssooooooossso+//  ::/+ooyyyyyyyyy|  */
/*	|yyyyyyssssyyyyso+ssyyyyys+::-\+-\-0---.----..://+o::::-      /sysso+ossooooo++/  //+oosssssysss|  */
/*	|yyyyyysssyyyyyoosyyyyyyyyyss+--/--------:----:::::::     ///sssssssyssoosoooo\ +++ossyyysyyyyyy|  */
/*	|ysyyyysyyyyyysssyyyyyyysssso+::::--::/+++/://::://+     ::+osyyhhhyysssssssssso+oossssyyyyyyyyy|  */
/*	|sssyysyyyyyyyyyyyyyyyyyysssoooo++/++++oooo+++////////\::::/+osyyhhyhyyyssssyyssooosyyyyyyyyyyyy|  */
/*	|sysyysyyyyyyyyyyyyyyyyyyyyssosoo++++o+oo++///::::|::::::|::::: +osyyhyyssssyyyyyysssyhhhyyyyyyy|  */
/*	╔═══╦═══╦═══╦══╦══╗yyyyyysyo////\                  \---/-        /+syyyssssyyyyhhyysyyyhyyyyyyyy|  */
/*	║╔═╗║╔══╣╔══╩╗╔╣╔═╣╗─╔══╦══╗oooooooooo++++o+++/:::/:::/++         /oyyyyssyyhhhhhyhhyhhhyyyyyyyy|  */
/*	║╚═╝║╚══╣║╔═╗║║║╚═╣║─║╔╗║╔╗║yysyyyso+++ssosoo+o+/::::::-:+ooo+        syyyyyyyhhyhhhhyyyyyyyyyyy|  */
/*	║╔╗╔╣╔══╣║╚╗║║║╚═╗║║─║╚╝║╚╝╚╗yyyssssoosoo++++++++:---:--:+oossso       oyysyyhhhhhhhhyhhyyhhyyyy|  */
/*	║║║║║╚══╣╚═╝╠╝╚╦═╝║╚═╣╔╗║ ═ ║ysyysssssoooooooo++++:----::+oossysso++    oyyhyyhhyhyyhyhyyhyhyyyy|  */
/*	╚╝╚╝╚═══╩═══╩══╩══╩══╩╝╚╩═══╝yyysssssooooo++++++//:---:/++oosssssysss+: osyhhhyhhyyhyyyyyyyyyyyy|  */
/* *************************************************************************************************** */

#include "ahrs.hpp"

/**
 * @brief расчёт ориентации
 * 
 * @param initOrientation начальное значение ориентации
 * @param dataIMU данные с БИНС(акселерометр(X, Y, Z), гироскоп(X, Y, Z), магнетометр(X, Y))
 * @param dataTime время с начала замера данных с датчиков
 * @return ориентация(тангаж, крен, рысканье)
 */
vectDouble2d_t	getOrientation(const vectDouble_t initOrientation, const vectDouble2d_t *dataIMU, const vectDouble_t *dataTime)
{
	vectDouble2d_t	resOrientation; // углы ориентации(тангаж, крен, рысканье)
	vectDouble_t	dataAccelerometer; // данные с акселерометра
	vectDouble_t	dataGyroscopePast; // данные с гироскопа на предыдущем шаге
	vectDouble_t	dataGyroscopeCurrent; // данные с гироскопа на нынешнем шаге
	vectDouble_t	dataMagnetometer; // данные с магнетометра
	vectDouble_t	angleAccelerometer; // углы, получаемые с акселерометра
	vectDouble_t	angleGyroscope; // углы получаемы с гироскопа
	vectDouble_t	angleMagnetometer; // углы получаемые с магнитометра

	for (unsigned int j = 0; j < 3; j++)
	{
		dataAccelerometer.push_back((*dataIMU)[0][j]);
		dataGyroscopePast.push_back((*dataIMU)[0][j + 3]);
		if (j < 2)
			dataMagnetometer.push_back((*dataIMU)[0][j + 6]);
	}
	resOrientation.push_back(dataGyroscopePast);
	angleAccelerometer = getAngleAccelerometer(&dataAccelerometer);
	for	(unsigned int i = 1; i < (*dataIMU).size(); i++)
	{
		dataAccelerometer.clear();
		dataMagnetometer.clear();
		for (unsigned int j = 0; j < 3; j++)
		{
			dataAccelerometer.push_back((*dataIMU)[i][j]);
			dataGyroscopeCurrent.push_back((*dataIMU)[i][j + 3]);
			if (j < 2)
				dataMagnetometer.push_back((*dataIMU)[i][j + 6]);
		}
		angleAccelerometer = getAngleAccelerometer(&dataAccelerometer);
		angleMagnetometer = getAngleMagnetometer(&dataMagnetometer);
		angleGyroscope = getAngleGyroscope(&(resOrientation[i - 1]), &dataGyroscopeCurrent, (*dataTime)[i] - (*dataTime)[i - 1]);
		resOrientation.push_back(complementaryFilter(&angleAccelerometer , &angleGyroscope, &angleMagnetometer));
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
vectDouble_t	getAngleAccelerometer(const vectDouble_t *dataAccelerometer)
{
	vectDouble_t	angleAccelerometer;

	// for (unsigned int i = 0; i < 2; i++)
	for (unsigned int i = 0; i < 2; i++)
		angleAccelerometer.push_back(std::atan2((*dataAccelerometer)[i], (*dataAccelerometer)[2]));
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
vectDouble_t	getAngleGyroscope(const vectDouble_t *dataGyroscopePast, const vectDouble_t *dataGyroscopeCurrent, const double dt)
{
	vectDouble_t	angleGyroscope;

	for (unsigned int i = 0; i < 2; i++)
		angleGyroscope.push_back(integralEuler((*dataGyroscopePast)[i], (*dataGyroscopeCurrent)[i], dt));
	angleGyroscope.push_back(absRad(integralEuler((*dataGyroscopePast)[2], (*dataGyroscopeCurrent)[2], dt))); 
	return(angleGyroscope);
}

/**
 * @brief вычисление углов ориентации на основе данных с магнитометра
 * 
 * @param dataMagnetometer данные с магнитометра(измерения по осям X, Y)
 * @return рысканье
 */
vectDouble_t	getAngleMagnetometer(const vectDouble_t *dataMagnetometer)
{
	vectDouble_t	angleMagnetometr;

	angleMagnetometr.push_back(absRad(-std::atan2((*dataMagnetometer)[0], (*dataMagnetometer)[1])));
	return(angleMagnetometr);
}

/**
 * @brief перевод в диапазон от 0 до 2*pi 
 * 
 * @param rad значение в радианах(от 0 до pi/-pi)
 * @return значение в радианах(от 0 до 2*pi)
 */
double	absRad(const double rad)
{
	if (rad < 0)
		return(M_PI + (M_PI + rad));
	else if (rad > 2*M_PI)
		return (rad - 2*M_PI);
	else
		return (rad);
}
