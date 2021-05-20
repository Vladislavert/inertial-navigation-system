/* *************************************************************************************************** */
/* 	|Author: Vladislavert              |sssssssssso++——+++osssssssssssssssssssssssssssssssssssssssss|  */
/* 	|e-mail: chuvarevan@mail.ru        |oooooo..   /   |    ./yyyyyyyyyyosshhhhhyyyyyyyyyyyyyyyyyyyy|  */
/* 	|estimatePositionWGS.cpp           |yysssso////  /syyyyyyyyyyyyyyy0    /yhhhhhyyyyyyyyyyyyyyyyyy|  */
/*	|__________________________________|yyyyyyyso+   /ssyyyyyyyyyyyyso    0yhhhhhhhhyhyyyyyyyyyyyyyy|  */
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

// #define DEBUG

#ifdef DEBUG
	#include "iostream"
	#include "draw.hpp"
#endif

/**
 * @brief оценка позиции в геоцентрической СК(WGS-84)
 * 
 * @param coordinateGeoElipse координаты точки старта в геоцентрической эллипсоидальной СК
 * @param dataIMU данные с БИНС(акселерометр(X, Y, Z), гироскоп(X, Y, Z), магнитометр(X, Y)). Фильтруются внутри функции
 * @param dataGNSS данные с ГНСС приёмника в WGS-84(широта, долгота, высота)
 * @param dataTime время с начала замера данных с датчиков
 * @return координаты в геоцентрической СК(WGS-84)(X, Y, Z)
 */
vectDouble2d_t	estimatePositionWGS(vectDouble2d_t *dataIMU, const vectDouble2d_t *dataGNSS, const vectDouble_t *dataTime)
{
	vectDouble2d_t			resCoordinateWGS; // результат оценки положения в ГСК
	vectDouble2d_t 			dataIMUTranspose((*dataIMU)[0].size()); // данные с БИНС(акселерометр(X, Y, Z), гироскоп(X, Y, Z), магнетометр(X, Y))
	vectDouble_t			startCoordinateGeoNormal; // координаты начала стартовой СК в геоцентрической нормальной СК
	Eigen::Vector3d			acceleration; // ускорение
	vector3d<vectDouble_t>	accelerationVec;
	vector3d<vectDouble_t>	veloucityVec;
	vector3d<vectDouble_t>	positionVec;
	Eigen::Vector3d			apparentAcceleration; // кажущееся ускорение
	vectDouble2d_t			orientation;
	vectDouble_t			temp;
	Eigen::Vector3d			gravityAcceleration;
	Eigen::Matrix3d			matrixRotation;
	double					g;

	for	(unsigned int i = 0; i < (*dataIMU)[0].size(); i++)
		for (unsigned int j = 0; j < (*dataIMU).size(); j++)
			dataIMUTranspose[i].push_back((*dataIMU)[j][i]);
	g = gravitationalAccelerationCalc(55.813984, 230);
	gravityAcceleration << 0, 0, g;
	temp.push_back(0);
	temp.push_back(0);
	temp.push_back(0.12);
	// фильтрация данных с БИНС
	// lowPassFilter(&dataIMUTranspose[0], dataTime, 0.02);
	// lowPassFilter(&dataIMUTranspose[1], dataTime, 0.02);
	// lowPassFilter(&dataIMUTranspose[2], dataTime, 0.02);
	// for	(unsigned int i = 0; i < (*dataIMU).size(); i++)
	// 	for (unsigned int j = 0; j < (*dataIMU)[i].size(); j++)
	// 		(*dataIMU)[i][j] = dataIMUTranspose[j][i];
	// определение ориентации с помощью Attitude and Heading Reference System(AHRS)
	orientation.push_back(temp);
	matrixRotation = rotationMatrix(orientation[0]);
	orientation = getOrientation(orientation[0], dataIMU, dataTime);
	for	(unsigned int i = 0; i < orientation.size(); i++)
	{
		apparentAcceleration << (*dataIMU)[i][0], (*dataIMU)[i][1], (*dataIMU)[i][2];
		matrixRotation = rotationMatrix(orientation[i]);
		acceleration = (matrixRotation.inverse() * apparentAcceleration) - gravityAcceleration;
		accelerationVec.x.push_back(acceleration[0]);
		accelerationVec.y.push_back(acceleration[1]);
		accelerationVec.z.push_back(acceleration[2]);
	}
	veloucityVec.x = integralEuler(dataTime, &accelerationVec.x);
	veloucityVec.y = integralEuler(dataTime, &accelerationVec.y);
	veloucityVec.z = integralEuler(dataTime, &accelerationVec.z);
	positionVec.x = integralEuler(dataTime, &veloucityVec.x);
	positionVec.y = integralEuler(dataTime, &veloucityVec.y);
	positionVec.z = integralEuler(dataTime, &veloucityVec.z);
	// перевод из эллипсоидальной геоцентрической СК(ГСК) в прямоугольную ГСК
	// начальная выставка, для получения координат стартовой СК в геоцентрической СК(WGS-84)
	startCoordinateGeoNormal = convertGeoElipseToGeoNormal(&(*dataGNSS)[0]); // передавать значения полученные в результате начальной выставки(средние значения)
	#ifdef DEBUG
		std::cout << "X c ГНСС = " << startCoordinateGeoNormal[0] << std::endl;
		std::cout << "Y c ГНСС = " << startCoordinateGeoNormal[1] << std::endl;
		std::cout << "Z c ГНСС = " << startCoordinateGeoNormal[2] << std::endl;
	#endif
	// определение позиции путём интегрирования данных с акселерометра, а также коррекция позиции с помощью ГНСС
	for (unsigned int i = 0; i < positionVec.x.size(); i++)
	{		
		temp.clear();
		temp.push_back(positionVec.x[i] + startCoordinateGeoNormal[0]);
		temp.push_back(positionVec.y[i] + startCoordinateGeoNormal[1]);
		temp.push_back(positionVec.z[i] + startCoordinateGeoNormal[2]);
		resCoordinateWGS.push_back(temp);
	}
	for	(unsigned int i = 0; i < resCoordinateWGS.size(); i++)
		resCoordinateWGS[i] = convertGeoNormalToGeoElipse(&resCoordinateWGS[i]);
	#ifdef DEBUG
		std::cout << "широта = " << resCoordinateWGS[0][0] << std::endl;
		std::cout << "долгота = " << resCoordinateWGS[0][1] << std::endl;
		std::cout << "высота = " << resCoordinateWGS[0][2] << std::endl;
	#endif
	return (resCoordinateWGS);
}