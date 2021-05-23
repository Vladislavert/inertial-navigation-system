/* *************************************************************************************************** */
/* 	|Author: Vladislavert              |sssssssssso++——+++osssssssssssssssssssssssssssssssssssssssss|  */
/* 	|e-mail: chuvarevan@mail.ru        |oooooo..   /   |    ./yyyyyyyyyyosshhhhhyyyyyyyyyyyyyyyyyyyy|  */
/* 	|mainTest.cpp                      |yysssso////  /syyyyyyyyyyyyyyy0    /yhhhhhyyyyyyyyyyyyyyyyyy|  */
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

#include "inputData.hpp"
#include "iostream"
#include "readFile.hpp"
#include "filters.hpp"
#include "calcProbabilityCharact.hpp"
#include "draw.hpp"
// #include <../eigen3/Eigen/Dense>
#include <../libraries/eigen3/Eigen/Dense>
#include "ahrs.hpp"
#include "gravitationalAccelerationCalc.hpp"

#define DEBUG

using namespace Eigen;

int main()
{
	const std::string	DIR_RESOURCES = "./resource/";
	std::string			switchTesting;
	std::ifstream		file;
	std::string			nameFile;
	vectString_t		str;
	vectDouble2d_t		dataINS; // данные с БИНС
	// для стандратного .csv файла
	// const unsigned int	indxGyro = 6; // значение индекса под которым начинаются измерения гироскопа
	// const unsigned int	indxMagnet = 9; // значение индекса под которым начинаются измерения магнитометра
	// const unsigned int	indxAcc = 0; // значение индекса под которым начинаются измерения акселерометра
	// const unsigned int	indxTime = 24; // значение индекса под которым начинаются измерения акселерометра
	// изменённый файл .csv
	const unsigned int	indxGyro = 3; // значение индекса под которым начинаются измерения гироскопа
	const unsigned int	indxMagnet = 6; // значение индекса под которым начинаются измерения магнитометра
	const unsigned int	indxAcc = 0; // значение индекса под которым начинаются измерения акселерометра
	const unsigned int	indxTime = 12; // значение индекса под которым начинаются измерения времени
	const unsigned int	indxOrient = 9; // значение индекса под которым начинаются измерения ориентации





	std::cout << std::endl << "calculate trajectory..." << std::endl;
	std::cout << "__________________________________________" << std::endl;
	// nameFile = DIR_RESOURCES + "Car_7Km.h.txt";
	// nameFile = DIR_RESOURCES + "move Y(2 meters).txt";
	// nameFile = DIR_RESOURCES + "scooter.txt";
	// nameFile = DIR_RESOURCES + "orientation360_2_chear.csv";
	// nameFile = DIR_RESOURCES + "orientation360_2_chear (useful data).csv";
	nameFile = DIR_RESOURCES + "pitch.csv";

	file.open(nameFile);

	if (checkOpenFile(file))
	{
		readStrFile(file, str);
		inputData(str, dataINS, 1);
		file.close();
		str.clear();
	}
	else
		std::exit(0);

	Vec		xAcceleration(dataINS.size()); 			// вектор значений ускорения свободного падения по оси X
	Vec		yAcceleration(dataINS.size()); 			// вектор значений ускорения свободного падения по оси Y
	Vec		zAcceleration(dataINS.size()); 			// вектор значений ускорения свободного падения по оси Z
	Vec		xAccelerationFilter; 	// вектор значений ускорения свободного падения по оси X после фильтрации
	Vec		yAccelerationFilter; 	// вектор значений ускорения свободного падения по оси Y после фильтрации
	Vec		zAccelerationFilter; 	// вектор значений ускорения свободного падения по оси Z после фильтрации
	Vec		time(dataINS.size());					// время в течение которого осуществляется замер
	Vec		xOrientationVec(dataINS.size()); 		// вектор содержащий ориентацию по оси X(тангаж)
	Vec		yOrientationVec(dataINS.size()); 		// вектор содержащий ориентацию по оси Y(крен)
	Vec		zOrientationVec(dataINS.size()); 		// вектор содержащий ориентацию по оси Z(рысканье)

	double	mean_xAcceleration; // математическое ожидание
	double	dispersion_xAcceleration; // дисперсия
	double	mean_yAcceleration; // математическое ожидание 
	double	dispersion_yAcceleration; // дисперсия
	double	mean_zAcceleration; // математическое ожидание 
	double	dispersion_zAcceleration; // дисперсия
	double	g; // ускорение силы тяжести

	g = gravitationalAccelerationCalc(0.959931, 190);

	double	*angleAccelerometer;
	double	*dataAccelerometer;
	double	*angleGyroscope;
	double	*dataGyroscope;
	double	*dataGyroscopePast;
	double	*angleMagnetometer;
	double	*dataMagnetometer;
	double	*orientation;

	dataAccelerometer = new double[3];
	angleAccelerometer = new double[2];
	dataGyroscope = new double[3];
	angleGyroscope = new double[3];
	dataMagnetometer = new double[2];
	angleMagnetometer = new double[1];
	orientation = new double[3];


	// начальная инициализация
	for (unsigned int i = 0; i < dataINS.size(); i++)
	{
		xAcceleration[i] = dataINS[i][indxAcc];
		yAcceleration[i] = dataINS[i][indxAcc + 1];
		zAcceleration[i] = -dataINS[i][indxAcc + 2];
		time[i] = dataINS[i][indxTime];
	}
	

	for (unsigned int i = 0; i < 3; i++)
	{
		orientation[i] = 0;//dataINS[0][6 + i]; // начальная выставка БИНС (углы ориентации равны 0)
		angleGyroscope[i] = 0;
		dataGyroscope[i] = dataINS[0][indxGyro + i];
	}
	angleGyroscope[2] = dataINS[0][indxOrient]*M_PI/180;
	orientation[2] = dataINS[0][indxOrient]*M_PI/180;
	xOrientationVec[0] = dataINS[0][13];//orientation[0]*180/M_1_PI;//*180/M_1_PI;
	yOrientationVec[0] = dataINS[0][14];//dataGyroscope[1];//*180/M_1_PI;
	zOrientationVec[0] = dataINS[0][12];//dataGyroscope[2];//*180/M_1_PI;
	xAccelerationFilter = lowPassFilter(xAcceleration, time, 0.02);
	yAccelerationFilter = lowPassFilter(yAcceleration, time, 0.02);
	zAccelerationFilter = lowPassFilter(zAcceleration, time, 0.02);
	// xOrientationVec[0] = orientation[0];
	// yOrientationVec[0] = orientation[1];
	// zOrientationVec[0] = orientation[2];
	// xOrientationVec[0] = angleGyroscope[0];
	// yOrientationVec[0] = angleGyroscope[1];
	// zOrientationVec[0] = angleGyroscope[2];
	dataAccelerometer[0] = xAccelerationFilter[0];
	dataAccelerometer[1] = yAccelerationFilter[0];
	dataAccelerometer[2] = zAccelerationFilter[0];

	for (unsigned int i = 0; i < 2; i++)
		dataMagnetometer[i] = dataINS[0][indxMagnet + i];
	angleAccelerometer = getAngleAccelerometer(dataAccelerometer);
	time[0] = dataINS[0][indxTime] / 1000;
	for (size_t i = 1; i < dataINS.size(); i++)
	{
		time[i] = dataINS[i][indxTime] / 1000;
		// std::cout << dataINS[i][24] << std::endl;
		// xAcceleration[i] = dataINS[i][0];
		// yAcceleration[i] = dataINS[i][1];
		// zAcceleration[i] = -dataINS[i][2];
		for (unsigned int j = 0; j < 3; j++)
		{
			dataGyroscope[j] = dataINS[i][indxGyro + j];
			// dataAccelerometer[j] = dataINS[i][indxAcc + j];
		}
		dataAccelerometer[0] = xAccelerationFilter[i];
		dataAccelerometer[1] = yAccelerationFilter[i];
		dataAccelerometer[2] = zAccelerationFilter[i];
		// std::cout << "data gyroscope z = " << dataGyroscope[2] << std::endl;
		for (unsigned int j = 0; j < 2; j++)
			dataMagnetometer[j] = dataINS[i][indxMagnet + j];
		angleMagnetometer = getAngleMagnetometer(dataMagnetometer);
		angleGyroscope = getAngleGyroscope(orientation, dataGyroscope, time[i] - time[i - 1]);
		angleAccelerometer = getAngleAccelerometer(dataAccelerometer);
		// angleGyroscope = getAngleGyroscope(angleGyroscope, dataGyroscope, time[i] - time[i - 1]);
		std::cout << "orientation x = " << angleMagnetometer[0]<< std::endl;
		// std::cout << "angle gyroscope x = " << time[i - 1] << std::endl; 

		// dataAccelerometer[0] = xAcceleration[i];
		// dataAccelerometer[1] = yAcceleration[i];
		// dataAccelerometer[2] = zAcceleration[i];
		orientation = complementaryFilter(angleAccelerometer , angleGyroscope, angleMagnetometer);
			// orientation = complementaryFilter(orientation , angleGyroscope, angleMagnetometer);
		xOrientationVec[i] = angleAccelerometer[0]*180/M_PI;
		yOrientationVec[i] = angleAccelerometer[1]*180/M_PI;
		zOrientationVec[i] = orientation[2]*180/M_PI;
		// xOrientationVec[i] = angleMagnetometer[0]*180/M_PI;//orientation[0]*180/M_PI;//angleGyroscope[0]*180/M_1_PI;
		// yOrientationVec[i] = dataMagnetometer[1]*180/M_1_PI;//orientation[1]*180/M_PI;
		// zOrientationVec[i] = angleMagnetometer[2]*180/M_1_PI;//orientation[2]*180/M_PI;
	}
	
	drawGraph(&time, &xOrientationVec, "orientation X", 1);
	// Plot plot;
	// plot.drawCurve(time, xOrientationVec).label("test");
	// plot.show();
	drawGraph(&time, &yOrientationVec, "orientation Y", 1);
	drawGraph(&time, &zOrientationVec, "orientation Z", 1);


	// --------------------------------------------реализация для проведения тестирования-------------------------------------------------------------------------------------
	/*
	Vec xAcceleration(dataINS.size()); 		// вектор значений ускорения свободного падения по оси X
	Vec yAcceleration(dataINS.size()); 		// вектор значений ускорения свободного падения по оси Y
	Vec zAcceleration(dataINS.size()); 		// вектор значений ускорения свободного падения по оси Z
	Vec xVeloucity;//(dataINS.size()); 		// вектор значений скорости по оси X
	Vec yVeloucity;//(dataINS.size()); 		// вектор значений скорости по оси Y
	Vec zVeloucity;//(dataINS.size()); 		// вектор значений скорости по оси Z
	Vec xCoordinate;//(dataINS.size()); 		// вектор значений координат по оси X
	Vec yCoordinate;//(dataINS.size()); 		// вектор значений координат по оси Y
	Vec zCoordinate;//(dataINS.size()); 		// вектор значений координат по оси Z
	Vec time(dataINS.size());				// время в течение которого осуществляется замер

	double	mean_xAcceleration; // математическое ожидание
	double	dispersion_xAcceleration; // дисперсия
	double	mean_yAcceleration; // математическое ожидание 
	double	dispersion_yAcceleration; // дисперсия
	double	mean_zAcceleration; // математическое ожидание 
	double	dispersion_zAcceleration; // дисперсия
	double	g; // ускорение силы тяжести

	g = gravitationalAccelerationCalc(0.959931, 190);
	double *dataAccelerometer;

	dataAccelerometer = new double[3];
	for (size_t i = 0; i < dataINS.size(); i++)
	{
		xAcceleration[i] = dataINS[i][0];
		yAcceleration[i] = dataINS[i][1];
		zAcceleration[i] = -dataINS[i][2] + g;
		dataAccelerometer[0] = xAcceleration[i];
		dataAccelerometer[1] = yAcceleration[i];
		dataAccelerometer[2] = zAcceleration[i];
			// getAngleFromAccelerometer(dataAccelerometer);
		time[i] = dataINS[i][24] / 1000;
	}
	

	getAngleFromAccelerometer(dataAccelerometer);

	Vec xAccelerationFilter;
	Vec yAccelerationFilter;
	Vec zAccelerationFilter;
	xAccelerationFilter = lowPassFilter(xAcceleration, time, 0.02);
	yAccelerationFilter = lowPassFilter(yAcceleration, time, 0.02);
	zAccelerationFilter = lowPassFilter(zAcceleration, time, 0.02);

	mean_xAcceleration = meanCalculate(xAcceleration);
	dispersion_xAcceleration = dispersionCalculate(xAcceleration, mean_xAcceleration);

	mean_yAcceleration = meanCalculate(yAcceleration);
	dispersion_yAcceleration = dispersionCalculate(yAcceleration, mean_yAcceleration);

	mean_zAcceleration = meanCalculate(zAcceleration);
	dispersion_zAcceleration = dispersionCalculate(zAcceleration, mean_zAcceleration);
	// xAccelerationFilter = lowPassFilter(xAccelerationFilter, time, 1);
	// yAccelerationFilter = lowPassFilter(yAccelerationFilter, time, 1);
	// zAccelerationFilter = lowPassFilter(zAccelerationFilter + g, time, 1);
	Plot plotX;
	Plot plotY;
	Plot plotZ;

	drawGraph(&time, &xAcceleration, &plotX, "acceleration X", 0);
	// drawLine(&time, &(3*sqrt(dispersion_xAcceleration) + mean_xAcceleration), &plotX, "SD", 0);
	drawLine(&time, &(mean_xAcceleration), &plotX, "mean", 1);
	// drawLine(&time, -3*sqrt(dispersion_xAcceleration) + mean_xAcceleration, &plotX, "SD", 1);

	drawGraph(&time, &yAcceleration, &plotY,"acceleration Y", 0);
	// drawLine(&time, 3*sqrt(dispersion_yAcceleration) + mean_yAcceleration, &plotY, "SD", 0);
	drawLine(&time, &mean_yAcceleration, &plotY, "mean", 0);
	// drawLine(&time, -3*sqrt(dispersion_yAcceleration) + mean_yAcceleration, &plotY, "SD", 1);

	drawGraph(&time, &zAcceleration, &plotZ,"acceleration Z", 0);
	// drawLine(time, 3*sqrt(dispersion_zAcceleration) + mean_zAcceleration, &plotZ, "SD", 0);
	drawLine(&time, &mean_zAcceleration, &plotZ, "mean", 0);
	// drawLine(time, -3*sqrt(dispersion_zAcceleration) + mean_zAcceleration, &plotZ, "SD", 1);

	xAcceleration = xAccelerationFilter;
	yAcceleration = yAccelerationFilter;
	zAcceleration = zAccelerationFilter;

	// drawLine(time, 3*sqrt(dispersion_xAcceleration), plot1,"line");
	// drawLine(time, -3*sqrt(dispersion_xAcceleration), "line");

	#ifdef DEBUG
		std::cout << "mean x = " << mean_xAcceleration << " "
				<< "dispersion x = "<< dispersion_xAcceleration << " "
				<< "3*sigma x = " << 3*sqrt(dispersion_xAcceleration) << std::endl;
		std::cout << "mean y = " << mean_yAcceleration << " "
				<< "dispersion y = " << dispersion_yAcceleration << " "
				<< "3*sigma x = " << 3*sqrt(dispersion_yAcceleration) << std::endl;
		std::cout << "mean z = " << mean_zAcceleration << " "
				<< "dispersion z = " << dispersion_zAcceleration << " "
				<< "3*sigma x = " << 3*sqrt(dispersion_zAcceleration) << std::endl;

		std::cout << "g = " << g << std::endl;
	#endif

	// std::cout << "mean X" << mean_xAcceleration << std::endl;
	// std::cout << "dispersion X" << dispersion_xAcceleration << std::endl;

	// std::cout << "mean Y" << mean_yAcceleration << std::endl;
	// std::cout << "dispersion Y" << dispersion_yAcceleration << std::endl;


	// std::cout << "mean Z" << mean_zAcceleration << std::endl;
	// std::cout << "dispersion Z" << dispersion_zAcceleration << std::endl;
	// for (size_t i = 0; i < dataINS.size(); i++)
	// {
			
	// }
	//dispersion_xAcceleration = 3 * std::sqrt(dispersion_xAcceleration);

	g = gravitationalAccelerationCalc(0.959931, 130);
	// double startValue = 000;
	double startValue = 0.000;
	Vec time1(xAcceleration.size() - startValue);
	Vec xAcceleration1(xAcceleration.size() - startValue);
	Vec yAcceleration1(xAcceleration.size() - startValue);
	Vec zAcceleration1(xAcceleration.size() - startValue);
	for	(int i = startValue; i < xAcceleration.size() - startValue; i++)
	{
		time1[i - startValue] = time[i];
		xAcceleration1[i - startValue] = xAcceleration[i];
		yAcceleration1[i - startValue] = yAcceleration[i];
		zAcceleration1[i - startValue] = zAcceleration[i];
	}

	// Plot plotX_filter;
	// Plot plotY_filter;
	// drawLine(time, 0.014, &plotX_filter, "SD", 0);
	Vec dataX = xAcceleration1 - mean_xAcceleration;
	Vec dataY = yAcceleration1 - mean_yAcceleration;
	Vec dataZ = zAcceleration1 - mean_zAcceleration;
	drawGraph(&time1, &(dataX), "acceleration filter X");	
	drawGraph(&time1, &(dataY), "acceleration filter Y");
	drawGraph(&time1, &(dataZ), "acceleration filter Z");


	xVeloucity = integralEuler(time1, xAcceleration1 - mean_xAcceleration);
	yVeloucity = integralEuler(time1, yAcceleration1 - mean_yAcceleration);
	zVeloucity = integralEuler(time1, zAcceleration1 - mean_zAcceleration);

	drawGraph(&time1, &xVeloucity, "veloucity X");
	drawGraph(&time1, &yVeloucity, "veloucity Y");
	drawGraph(&time1, &zVeloucity, "veloucity Z");

	#ifdef DEBUG
		std::cout << "value veloucityY = " << yVeloucity[yVeloucity.size() - 2] << std::endl;
	#endif

	// xCoordinate = integralEuler(time1, xVeloucity);
	// yCoordinate = integralEuler(time1, yVeloucity);
	// zCoordinate = integralEuler(time1, zVeloucity);

	// drawGraph(&time1, &xCoordinate, "coordinate X");
	// drawGraph(&time1, &yCoordinate, "coordinate Y");
	// drawGraph(&time1, &zCoordinate, "coordinate Z");*/
	

	// расчитать мат ожидание и дисперсию

}
