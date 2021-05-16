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

#define DEBUG

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


	// for	(unsigned int i = 0; i < (*dataIMU)[0].size(); i++)
	// 	for (unsigned int j = 0; j < (*dataIMU).size(); j++)
	// 		dataIMUTranspose[i].push_back((*dataIMU)[j][i]);
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
	#ifdef DEBUG
		vectDouble_t		xOrientation;
		vectDouble_t		yOrientation;
		vectDouble_t		zOrientation;
		Plot				plotOrientationX;
		Plot				plotOrientationY;
		Plot				plotOrientationZ;
		vectPlot2d_t		plotOrientationXYZ(3);

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
		drawGraph(dataTime, &xOrientation, &plotOrientationX, "xOrientation", 0);
		drawGraph(dataTime, &yOrientation, &plotOrientationY, "yOrientation", 0);
		drawGraph(dataTime, &zOrientation, &plotOrientationZ, "zOrientation", 0);
		plotOrientationXYZ[0].push_back(plotOrientationX);
		plotOrientationXYZ[1].push_back(plotOrientationY);
		plotOrientationXYZ[2].push_back(plotOrientationZ);
		Figure				figOrientation = plotOrientationXYZ;

		figOrientation.size(600, 600);
		figOrientation.show();
	#endif
	for	(unsigned int i = 0; i < (*dataIMU).size(); i++)
	{
		apparentAcceleration << (*dataIMU)[i][0], (*dataIMU)[i][1], (*dataIMU)[i][2];
		orientation = getOrientation(orientation[i], dataIMU, dataTime);
		matrixRotation = rotationMatrix(orientation[i]);
		// acceleration = apparentAcceleration - (matrixRotation * gravityAcceleration);
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
	#ifdef DEBUG
		Plot				plotPositionX;
		Plot				plotPositionY;
		Plot				plotPositionZ;
		Plot				plotVeloucityX;
		Plot				plotVeloucityY;
		Plot				plotVeloucityZ;
		vectPlot2d_t		plotPositionXYZ(3);
		vectPlot2d_t		plotVeloucityXYZ(3);

		drawGraph(dataTime, &positionVec.x, &plotPositionX, "xPosition", 0);
		drawGraph(dataTime, &positionVec.y, &plotPositionY, "yPosition", 0);
		drawGraph(dataTime, &positionVec.z, &plotPositionZ, "zPosition", 0);
		plotPositionXYZ[0].push_back(plotPositionX);
		plotPositionXYZ[1].push_back(plotPositionY);
		plotPositionXYZ[2].push_back(plotPositionZ);
		Figure				figPosition = plotPositionXYZ;
		figPosition.size(600, 600);
		figPosition.show();

		drawGraph(dataTime, &accelerationVec.x, &plotVeloucityX, "xAcceleration", 0);
		drawGraph(dataTime, &accelerationVec.y, &plotVeloucityY, "yAcceleration", 0);
		drawGraph(dataTime, &accelerationVec.z, &plotVeloucityZ, "zAcceleration", 0);
		plotVeloucityXYZ[0].push_back(plotVeloucityX);
		plotVeloucityXYZ[1].push_back(plotVeloucityY);
		plotVeloucityXYZ[2].push_back(plotVeloucityZ);
		Figure				figVeloucity = plotVeloucityXYZ;
		figVeloucity.size(600, 600);
		figVeloucity.show();


		
	#endif
	// перевод из эллипсоидальной геоцентрической СК(ГСК) в прямоугольную ГСК
	// начальная выставка, для получения координат стартовой СК в геоцентрической СК(WGS-84)
	startCoordinateGeoNormal = convertGeoElipseToGeoNormal(&(*dataGNSS)[0]); // передавать значения полученные в результате начальной выставки(средние значения)
	
	// перевод из связанной СК(ССК) в связанные нормальные оси(СНС), с помощью матрицы поворотов, для опеределения позиции в стартовой СК
	// определение позиции путём интегрирования данных с акселерометра, а также коррекция позиции с помощью ГНСС
	// перевод из стартовой СК в ГСК
	return (resCoordinateWGS);
}