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

#include "estimatePositionWGS.hpp"

/**
 * @brief 
 * 
 * @param dataIMU 
 * @param dataGNSS 
 * @param time 
 * @return 
 */

/**
 * @brief оценка позиции в геоцентрической СК(WGS-84)
 * 
 * @param coordinateGeoElipse координаты точки старта в геоцентрической эллипсоидальной СК
 * @param dataIMU данные с БИНС(акселерометр(X, Y, Z), гироскоп(X, Y, Z), магнетометр(X, Y))
 * @param dataGNSS данные с ГНСС приёмника в WGS-84(широта, долгота, высота)
 * @param dataTime время с начала замера данных с датчиков
 * @return координаты в геоцентрической СК(WGS-84)(X, Y, Z)
 */
vectDouble2d_t	estimatePositionWGS(const vectDouble2d_t *dataIMU, const vectDouble2d_t *dataGNSS, const vectDouble_t *dataTime)
{
	vectDouble2d_t		resCoordinateWGS; // результат оценки положения в ГСК
	vectDouble_t		startCoordinateGeoNormal; // координаты начала стартовой СК в геоцентрической нормальной СК
	Eigen::Vector3d		acceleration;
	vectDouble2d_t		orientation;
	vectDouble_t		temp;
	Eigen::Vector3d		gravityAcceleration(0, 0, 9.81);
	Eigen::Matrix3d		matrixRotation;

	temp.push_back(0);
	temp.push_back(0);
	temp.push_back(0.12);
	orientation.push_back(temp);
	matrixRotation = rotationMatrix(orientation[0]);
	acceleration = matrixRotation * gravityAcceleration;
	// перевод из эллипсоидальной геоцентрической СК(ГСК) в прямоугольную ГСК
	// начальная выставка, для получения координат стартовой СК в геоцентрической СК(WGS-84)
	startCoordinateGeoNormal = convertGeoElipseToGeoNormal(&(*dataGNSS)[0]); // передавать значения полученные в результате начальной выставки(средние значения)
	
	// перевод из связанной СК(ССК) в связанные нормальные оси(СНС), с помощью матрицы поворотов, для опеределения позиции в стартовой СК
	// определение позиции путём интегрирования данных с акселерометра, а также коррекция позиции с помощью ГНСС
	// перевод из стартовой СК в ГСК
	return (resCoordinateWGS);
}