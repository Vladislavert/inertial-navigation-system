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
 * @brief вычисление углов ориентации на основе данных с акселерометра
 * 
 * @param dataAccelerometer данные с акселерометра(кажущееся ускорение по связанным осям)
 * @return углы ориентации(тангаж, крен)
 */
double	*getAngleAccelerometer(const double dataAccelerometer[3])
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
	angleGyroscope[2] = absRad(angleGyroscope[2]); 
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
	angleMagnetometr[0] = -std::atan2(dataMagnetometer[0], dataMagnetometer[1]);
	angleMagnetometr[0] = absRad(angleMagnetometr[0]);
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
