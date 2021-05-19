/* *************************************************************************************************** */
/* 	|Author: Vladislavert              |sssssssssso++——+++osssssssssssssssssssssssssssssssssssssssss|  */
/* 	|e-mail: chuvarevan@mail.ru        |oooooo..   /   |    ./yyyyyyyyyyosshhhhhyyyyyyyyyyyyyyyyyyyy|  */
/* 	|applicationStart.cpp              |yysssso////  /syyyyyyyyyyyyyyy0    /yhhhhhyyyyyyyyyyyyyyyyyy|  */
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

#include "applicationStart.hpp"

#define DEBUG

#ifdef DEBUG
	#include "iostream"
#endif


void	applicationStart()
{	
	
	const std::string	DIR_RESOURCES = "./resource/";
	std::ifstream		file;
	std::ifstream		fileInit;
	std::string			nameFile;
	std::string			nameFileInitExhibition;
	vectString_t		str;
	vectDouble2d_t		dataSensors; // данные с датчиков
	vectDouble2d_t		dataSensorsInit; // данные с датчиков во время начальной инициалзиации
	vectDouble2d_t		positionWGS; // оценка позиции в WGS84(X, Y, Z)
	vectDouble_t		xPositionWGS;
	vectDouble_t		yPositionWGS;
	vectDouble_t		zPositionWGS;
	double				*meanAcc;
	double				*dispersionAcc;
	double				*meanGyro;
	double				*dispersionGyro;
	double				g;

	// nameFile = DIR_RESOURCES + "orientation360_2_chear (useful data).csv";
	// nameFile = DIR_RESOURCES + "Move(orientation_30, 6 meters).csv";
	// nameFile = DIR_RESOURCES + "move_long_meters.csv";
	nameFile = DIR_RESOURCES + "initCondition2.csv";
	nameFileInitExhibition = DIR_RESOURCES + "initCondition2.csv";
	file.open(nameFile);
	fileInit.open(nameFileInitExhibition);
	if (checkOpenFile(file) && checkOpenFile(fileInit))
	{
		readStrFile(file, str);
		inputData(str, dataSensors, 1);
		str.clear();
		file.close();
		readStrFile(fileInit, str);
		inputData(str, dataSensorsInit, 1);
		fileInit.close();
		str.clear();
	}
	else
	{
		std::cout << "error open file" << std::endl;
		std::exit(0);
	}
	// запись данных с сенсоров из общего вектора в вектор соответсвующие типу датчик
	vectDouble2d_t 		dataIMU; // данные с БИНС(акселерометр(X, Y, Z), гироскоп(X, Y, Z), магнетометр(X, Y))
	vectDouble2d_t 		dataIMUInit; // данные с БИНС(акселерометр(X, Y, Z), гироскоп(X, Y, Z), магнетометр(X, Y)) для начальной выставки
	vectDouble2d_t		dataGNSS; // данные с ГНСС(широта, долгота, высота)
	vectDouble_t		dataTime; // время с начала замера данных с датчиков
	vectDouble_t		dataTimeInit; // время с начала замера данных с датчиков
	vectDouble_t		temp; // временый вектор, для заполнения
	vectDouble_t		tempInit; // временый вектор, для заполнения данных начальной выставки

	for	(unsigned int i = 0; i < dataSensors.size(); i++)
	{
		for (unsigned int j = 0; j < 3; j++)
			temp.push_back(dataSensors[i][indxAcc + j]);
		for (unsigned int j = 0; j < 3; j++)
			temp.push_back(dataSensors[i][indxGyro + j]);

		for (unsigned int j = 0; j < 2; j++)
			temp.push_back(dataSensors[i][indxMagnet + j]);
		dataIMU.push_back(temp);
		temp.clear();
		for (unsigned int j = 0; j < 3; j++)
			temp.push_back(0);
		dataGNSS.push_back(temp);
		dataTime.push_back(dataSensors[i][indxTime] / 1000);
		temp.clear();
	}
	for	(unsigned int i = 0; i < dataSensorsInit.size(); i++)
	{
		for (unsigned int j = 0; j < 3; j++)
			tempInit.push_back(dataSensorsInit[i][indxAcc + j]);
		for (unsigned int j = 0; j < 3; j++)
			tempInit.push_back(dataSensorsInit[i][indxGyro + j]);
		for (unsigned int j = 0; j < 2; j++)
			tempInit.push_back(dataSensorsInit[i][indxMagnet + j]);
		dataIMUInit.push_back(tempInit);
		tempInit.clear();
		dataTimeInit.push_back(dataSensorsInit[i][indxTime] / 1000);
		tempInit.clear();
	}
	#ifdef DEBUG
		vectDouble2d_t 		dataIMUTranspose(dataIMU[0].size()); // данные с БИНС(акселерометр(X, Y, Z), гироскоп(X, Y, Z), магнетометр(X, Y))
		vectDouble2d_t 		dataIMUTransposeInit(dataIMUInit[0].size()); // данные с БИНС(акселерометр(X, Y, Z), гироскоп(X, Y, Z), магнетометр(X, Y))
		Plot				plotPositionX;
		Plot				plotPositionY;
		Plot				plotPositionZ;
		Plot				plotPositionXInit;
		Plot				plotPositionYInit;
		Plot				plotPositionZInit;				
		vectPlot2d_t		plotPositionXYZ(3);
		vectPlot2d_t		plotPositionXYZInit(3);

		for	(unsigned int i = 0; i < dataIMU[0].size(); i++)
			for (unsigned int j = 0; j < dataIMU.size(); j++)
				dataIMUTranspose[i].push_back(dataIMU[j][i]);

		for	(unsigned int i = 0; i < dataIMUInit[0].size(); i++)
			for (unsigned int j = 0; j < dataIMUInit.size(); j++)
				dataIMUTransposeInit[i].push_back(dataIMUInit[j][i]);

		drawGraph(&dataTime, &dataIMUTranspose[0], &plotPositionX, "x acceleration not filters", 0);
		drawGraph(&dataTime, &dataIMUTranspose[1], &plotPositionY, "y acceleration not filters", 0);
		drawGraph(&dataTime, &dataIMUTranspose[2], &plotPositionZ, "z acceleration not filters", 0);
		double valueMean = -0.0384793;
		double valueDispersion =  0.0307339;
		drawLine(&dataTime, &(valueMean), &plotPositionX, "mean accelerometer x", 0);
		drawLine(&dataTime, &(valueDispersion += valueMean), &plotPositionX, "3 sigma accelerometer x", 0);
		drawLine(&dataTime, &(((valueDispersion -= valueMean) *= -1) += valueMean), &plotPositionX, "-3 sigma accelerometer x", 0);
		valueMean = -0.0123196;
		valueDispersion =  0.0317942;
		drawLine(&dataTime, &(valueMean), &plotPositionY, "mean accelerometer y", 0);
		drawLine(&dataTime, &(valueDispersion += valueMean), &plotPositionY, "3 sigma accelerometer y", 0);
		drawLine(&dataTime, &(((valueDispersion -= valueMean) *= -1) += valueMean), &plotPositionY, "-3 sigma accelerometer y", 0);
		valueMean =  9.87194;
		valueDispersion =  0.0412238;
		drawLine(&dataTime, &(valueMean), &plotPositionZ, "mean accelerometer z", 0);
		drawLine(&dataTime, &(valueDispersion += valueMean), &plotPositionZ, "3 sigma accelerometer z", 0);
		drawLine(&dataTime, &(((valueDispersion -= valueMean) *= -1) += valueMean), &plotPositionZ, "-3 sigma accelerometer z", 0);
		plotPositionX.grid().show();
		plotPositionY.grid().show();
		plotPositionZ.grid().show();
		plotPositionXYZ[0].push_back(plotPositionX);
		plotPositionXYZ[1].push_back(plotPositionY);
		plotPositionXYZ[2].push_back(plotPositionZ);
		Figure				figPosition = plotPositionXYZ;
		figPosition.size(1200, 800);
		// figPosition.save("accel.png");
		figPosition.show();

		drawGraph(&dataTimeInit, &dataIMUTransposeInit[0], &plotPositionXInit, "xAccelerationNotFiltersInit", 0);
		drawGraph(&dataTimeInit, &dataIMUTransposeInit[1], &plotPositionYInit, "yAccelerationNotFiltersInit", 0);
		drawGraph(&dataTimeInit, &dataIMUTransposeInit[2], &plotPositionZInit, "zAccelerationNotFiltersInit", 0);
		plotPositionXYZInit[0].push_back(plotPositionXInit);
		plotPositionXYZInit[1].push_back(plotPositionYInit);
		plotPositionXYZInit[2].push_back(plotPositionZInit);
		Figure				figPositionInit = plotPositionXYZInit;
		figPositionInit.size(600, 600);
		figPositionInit.show();
	#endif
	g = gravitationalAccelerationCalc(55.813984, 230); // данные для начальной выставки
	getCorrectData(dataIMU, dataIMUInit, g);
	#ifdef DEBUG
		vectDouble2d_t 		dataIMUTranspose1(dataIMU[0].size()); // данные с БИНС(акселерометр(X, Y, Z), гироскоп(X, Y, Z), магнетометр(X, Y))
		for	(unsigned int i = 0; i < dataIMU[0].size(); i++)
			for (unsigned int j = 0; j < dataIMU.size(); j++)
				dataIMUTranspose1[i].push_back(dataIMU[j][i]);
		// lowPassFilter(&dataIMUTranspose1[0], &dataTime, 0.02);
		// lowPassFilter(&dataIMUTranspose1[1], &dataTime, 0.02);
		// lowPassFilter(&dataIMUTranspose1[2], &dataTime, 0.02);
	#endif
	

	
	#ifdef DEBUG
		
		Plot				plotPositionX1;
		Plot				plotPositionY1;
		Plot				plotPositionZ1;
		vectPlot2d_t		plotPositionXYZ1(3);


		drawGraph(&dataTime, &dataIMUTranspose1[0], &plotPositionX1, "x acceleration not filters", 0);
		drawGraph(&dataTime, &dataIMUTranspose1[1], &plotPositionY1, "yAcceleration not filters", 0);
		drawGraph(&dataTime, &dataIMUTranspose1[2], &plotPositionZ1, "zAcceleration not filters", 0);
		double valueMean1 = 0;
		double valueDispersion1 = 0.0307339;
		drawLine(&dataTime, &(valueMean1), &plotPositionX1, "mean accelerometer x", 0);
		drawLine(&dataTime, &(valueDispersion1 += valueMean1), &plotPositionX1, "3 sigma accelerometer x", 0);
		drawLine(&dataTime, &(((valueDispersion1 -= valueMean1) *= -1) += valueMean1), &plotPositionX1, "-3 sigma accelerometer x", 0);
		valueMean1 = 0;
		valueDispersion1 = 0.0317942;
		drawLine(&dataTime, &(valueMean1), &plotPositionY1, "mean accelerometer x", 0);
		drawLine(&dataTime, &(valueDispersion1 += valueMean1), &plotPositionY1, "3 sigma accelerometer x", 0);
		drawLine(&dataTime, &(((valueDispersion1 -= valueMean1) *= -1) += valueMean1), &plotPositionY1, "-3 sigma accelerometer x", 0);
		valueMean1 = g;
		valueDispersion1 = 0.0412238;
		drawLine(&dataTime, &(valueMean1), &plotPositionZ1, "mean accelerometer x", 0);
		drawLine(&dataTime, &(valueDispersion1 += valueMean1), &plotPositionZ1, "3 sigma accelerometer x", 0);
		drawLine(&dataTime, &(((valueDispersion1 -= valueMean1) *= -1) += valueMean1), &plotPositionZ1, "-3 sigma accelerometer x", 0);
		plotPositionX1.grid().show();
		plotPositionY1.grid().show();
		plotPositionZ1.grid().show();
		plotPositionXYZ1[0].push_back(plotPositionX1);
		plotPositionXYZ1[1].push_back(plotPositionY1);
		plotPositionXYZ1[2].push_back(plotPositionZ1);
		Figure				figPosition1 = plotPositionXYZ1;
		figPosition1.size(600, 600);
		figPosition1.size(1200, 800);
		figPosition1.save("accelFilters.png");
		figPosition1.show();
	#endif
	positionWGS = estimatePositionWGS(&dataIMU, &dataGNSS, &dataTime);
	#ifdef DEBUG
		for	(unsigned int i = 0; i < positionWGS.size(); i++)
		{
			for (unsigned int j = 0; j < positionWGS[i].size(); j++)
			{
				std::cout << positionWGS[i][j] << " ";
			}
			xPositionWGS.push_back(positionWGS[i][0]);
			yPositionWGS.push_back(positionWGS[i][1]);
			zPositionWGS.push_back(positionWGS[i][2]);
			std::cout << std::endl;
		}		
	#endif
	for	(unsigned int i = 0; i < positionWGS.size(); i++)
	{
		// for (unsigned int j = 0; j < positionWGS[i].size(); j++)
		// {
		// 	std::cout << positionWGS[i][j] << " ";
		// }
		xPositionWGS.push_back(positionWGS[i][0]);
		yPositionWGS.push_back(positionWGS[i][1]);
		zPositionWGS.push_back(positionWGS[i][2]);
		// std::cout << std::endl;
	}	
	// vectPlot2d_t		plotPositionXYZ(3);
	// Plot				plotPositionX;
	// Plot				plotPositionY;
	// Plot				plotPositionZ;
	// drawGraph(&dataTime, &xPositionWGS, &plotPositionX, "xPosition", 0);
	// drawGraph(&dataTime, &yPositionWGS, &plotPositionY, "yPosition", 0);
	// drawGraph(&dataTime, &zPositionWGS, &plotPositionZ, "zPosition", 0);
	// plotPositionXYZ[0].push_back(plotPositionX);
	// plotPositionXYZ[1].push_back(plotPositionY);
	// plotPositionXYZ[2].push_back(plotPositionZ);
	// Figure				figPosition = plotPositionXYZ;
	// figPosition.size(600, 600);
	// figPosition.show();

}