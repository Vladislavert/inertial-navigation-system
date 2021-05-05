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

// #define DEBUG

#ifdef DEBUG
	#include "iostream"
	#include "draw.hpp"
#endif

/**
 * @brief оценка позиции в геоцентрической СК(WGS-84)
 * 
 * @param coordinateGeoElipse координаты точки старта в геоцентрической эллипсоидальной СК
 * @param dataIMU данные с БИНС(акселерометр(X, Y, Z), гироскоп(X, Y, Z), магнетометр(X, Y)). Фильтруются внутри функции
 * @param dataGNSS данные с ГНСС приёмника в WGS-84(широта, долгота, высота)
 * @param dataTime время с начала замера данных с датчиков
 * @return координаты в геоцентрической СК(WGS-84)(X, Y, Z)
 */
vectDouble2d_t	estimatePositionWGS(vectDouble2d_t *dataIMU, const vectDouble2d_t *dataGNSS, const vectDouble_t *dataTime)
{
	vectDouble2d_t		resCoordinateWGS; // результат оценки положения в ГСК
	vectDouble_t		startCoordinateGeoNormal; // координаты начала стартовой СК в геоцентрической нормальной СК
	Eigen::Vector3d		acceleration; // ускорение
	vectDouble_t		accelerationVecX; // ускорение по оси X
	vectDouble_t		accelerationVecY; // ускорение по оси Y
	vectDouble_t		accelerationVecZ; // ускорение по оси Z
	vectDouble_t		veloucityVecX; // ускорение по оси X
	vectDouble_t		veloucityVecY; // ускорение по оси Y
	vectDouble_t		veloucityVecZ; // ускорение по оси Z
	vectDouble_t		positionVecX; // ускорение по оси X
	vectDouble_t		positionVecY; // ускорение по оси Y
	vectDouble_t		positionVecZ; // ускорение по оси Z
	Eigen::Vector3d		apparentAcceleration; // кажущееся ускорение
	vectDouble2d_t		orientation;
	vectDouble_t		temp;
	Eigen::Vector3d		gravityAcceleration;
	Eigen::Matrix3d		matrixRotation;
	double				g;

	g = gravitationalAccelerationCalc(0.959931, 230);
	gravityAcceleration << 0, 0, g;
	temp.push_back(0);
	temp.push_back(0);
	temp.push_back(0.12);
	// фильтрация данных с БИНС
	// lowPassFilter(&(*dataIMU)[0], dataTime, 0.02);
	// определение ориентации с помощью Attitude and Heading Reference System(AHRS)
	orientation.push_back(temp);
	matrixRotation = rotationMatrix(orientation[0]);
	orientation = getOrientation(orientation[0], dataIMU, dataTime);
	#ifdef DEBUG
		vectDouble_t		xOrientation;
		vectDouble_t		yOrientation;
		vectDouble_t		zOrientation;
		for	(unsigned int i = 0; i < orientation.size(); i++)
		{
			for (unsigned int j = 0; j < orientation[i].size(); j++)
			{
				std::cout << orientation[i][j] << " ";		
			}
			std::cout << std::endl;
			xOrientation.push_back(orientation[i][0]);
			yOrientation.push_back(orientation[i][1]);
			zOrientation.push_back(orientation[i][2]);
		}
		drawGraph(dataTime, &xOrientation, "xOrientation");
		drawGraph(dataTime, &yOrientation, "yOrientation");
		drawGraph(dataTime, &zOrientation, "zOrientation");
	#endif
	for	(unsigned int i = 0; i < (*dataIMU).size(); i++)
	{
		apparentAcceleration << (*dataIMU)[i][0], (*dataIMU)[i][1], (*dataIMU)[i][2];
		orientation = getOrientation(orientation[i], dataIMU, dataTime);
		matrixRotation = rotationMatrix(orientation[i]);
		acceleration = apparentAcceleration - (matrixRotation * gravityAcceleration);
		accelerationVecX.push_back(acceleration[0]);
		accelerationVecY.push_back(acceleration[1]);
		accelerationVecZ.push_back(acceleration[2]);
	}
	veloucityVecX = integralEuler(dataTime, &accelerationVecX);
	veloucityVecY = integralEuler(dataTime, &accelerationVecY);
	veloucityVecZ = integralEuler(dataTime, &accelerationVecZ);
	positionVecX = integralEuler(dataTime, &veloucityVecX);
	positionVecY = integralEuler(dataTime, &veloucityVecY);
	positionVecZ = integralEuler(dataTime, &veloucityVecZ);
	#ifdef DEBUG
		drawGraph(dataTime, &positionVecX, "xPosition");
		drawGraph(dataTime, &positionVecY, "yPosition");
		drawGraph(dataTime, &positionVecZ, "zPosition");
	#endif
	// перевод из эллипсоидальной геоцентрической СК(ГСК) в прямоугольную ГСК
	// начальная выставка, для получения координат стартовой СК в геоцентрической СК(WGS-84)
	startCoordinateGeoNormal = convertGeoElipseToGeoNormal(&(*dataGNSS)[0]); // передавать значения полученные в результате начальной выставки(средние значения)
	
	// перевод из связанной СК(ССК) в связанные нормальные оси(СНС), с помощью матрицы поворотов, для опеределения позиции в стартовой СК
	// определение позиции путём интегрирования данных с акселерометра, а также коррекция позиции с помощью ГНСС
	// перевод из стартовой СК в ГСК
	for (unsigned int i = 0; i < positionVecX.size(); i++)
	{		
		temp.clear();
		temp.push_back(positionVecX[i]);
		temp.push_back(positionVecY[i]);
		temp.push_back(positionVecZ[i]);
		resCoordinateWGS.push_back(temp);
	}
	
	return (resCoordinateWGS);
}