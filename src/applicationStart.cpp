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

void	applicationStart()
{
	const std::string	DIR_RESOURCES = "./resource/";
	std::ifstream		file;
	std::ifstream		fileInit;
	std::ifstream		fileInitGNSS;
	std::string			nameFile; // название файла с основными данными
	std::string			nameFileInitExhibition; // название файла, где проводится определения ошибок датчиков(переименовать??)
	std::string			nameFileInitGNSS; // название файла с ГНСС, для накопления начальной позиции
	vectString_t		strTemp;
	vectDouble2d_t		dataSensors; // данные с датчиков
	vectDouble2d_t		dataFileInitGNSS; // данные для определения позиции
	vectDouble2d_t		dataSensorsInit; // данные с датчиков во время начальной инициализации
	vectDouble2d_t		positionWGS; // оценка позиции в WGS84(X, Y, Z)
	vectDouble_t		xPositionWGS;
	vectDouble_t		yPositionWGS;
	vectDouble_t		zPositionWGS;
	vectPlot2d_t		plotPositionXYZ(quantityAxes);
	Plot				plotPositionX;
	Plot				plotPositionY;
	Plot				plotPositionZ;
	double				g;
	double				*meanGNSS;

	// nameFile = DIR_RESOURCES + "GNSSup_0.csv";
	// nameFileInitGNSS = DIR_RESOURCES + "initGNSSup_0.csv";
	// nameFileInitExhibition = DIR_RESOURCES + "initCondition2.csv";
	// временные имена файлов
	nameFile = DIR_RESOURCES + "initCondition2.csv";
	nameFileInitGNSS = DIR_RESOURCES + "initCondition2.csv";
	//------------------------------------------------
	// Тестирование магнитометра
	// nameFile = DIR_RESOURCES + "testMagnetometer.csv";
	// nameFileInitGNSS = DIR_RESOURCES + "testMagnetometerExhibition.csv";
	// END---------------------------------------
	// nameFile = DIR_RESOURCES + "car_60kmh.csv";
	// nameFileInitGNSS = DIR_RESOURCES + "carExhibition_60kmh.csv";
	nameFileInitExhibition = DIR_RESOURCES + "initCondition2.csv";
	file.open(nameFile);
	fileInit.open(nameFileInitExhibition);
	fileInitGNSS.open(nameFileInitGNSS);
	if (checkOpenFile(file) && checkOpenFile(fileInit))
	{
		readStrFile(file, strTemp);
		inputData(strTemp, dataSensors, 1);
		strTemp.clear();
		file.close();
		readStrFile(fileInit, strTemp);
		inputData(strTemp, dataSensorsInit, 1);
		strTemp.clear();
		fileInit.close();
		readStrFile(fileInitGNSS, strTemp);
		inputData(strTemp, dataFileInitGNSS, 1);
		strTemp.clear();
		fileInit.close();
	}
	else
	{
		std::cout << "error open file" << std::endl;
		std::exit(0);
	}
	// запись данных с сенсоров из общего вектора в вектор соответствующие типу датчик
	vectDouble2d_t 		dataIMU; // данные с БИНС(акселерометр(X, Y, Z), гироскоп(X, Y, Z), магнетометр(X, Y))
	vectDouble2d_t 		dataIMUInit; // данные с БИНС(акселерометр(X, Y, Z), гироскоп(X, Y, Z), магнетометр(X, Y)) для начальной выставки
	vectDouble2d_t		dataGNSS; // данные с ГНСС(широта, долгота, высота)
	vectDouble2d_t		dataInitGNSS; // данные с ГНСС(широта, долгота, высота)
	vectDouble_t		dataTime; // время с начала замера данных с датчиков
	vectDouble_t		dataTimeInit; // время с начала замера данных с датчиков
	vectDouble_t		temp; // временный вектор, для заполнения
	vectDouble_t		tempInit; // временный вектор, для заполнения данных начальной выставки

	for	(unsigned int i = 0; i < dataSensors.size(); i++)
	{
		for (unsigned int j = 0; j < quantityAxes; j++)
			temp.push_back(dataSensors[i][indxAcc + j]);
		for (unsigned int j = 0; j < quantityAxes; j++)
			temp.push_back(dataSensors[i][indxGyro + j]);
		for (unsigned int j = 0; j < quantityAxes - 1; j++)
			temp.push_back(dataSensors[i][indxMagnet + j]);
		dataIMU.push_back(temp);
		temp.clear();
		for (unsigned int j = 0; j < quantityAxes; j++)
			temp.push_back(dataSensors[i][indxGNSS + j]);
		dataGNSS.push_back(temp);
		dataTime.push_back(dataSensors[i][indxTime] / 1000);
		temp.clear();		
	}
	for	(unsigned int i = 0; i < dataFileInitGNSS.size(); i++)
	{	
		temp.clear();
		for (unsigned int j = 0; j < quantityAxes; j++)
			temp.push_back(dataFileInitGNSS[i][indxInitGNSS + j]);
		dataInitGNSS.push_back(temp);
	}
	for	(unsigned int i = 0; i < dataSensorsInit.size(); i++)
	{
		for (unsigned int j = 0; j < quantityAxes; j++)
			tempInit.push_back(dataSensorsInit[i][indxAcc + j]);
		for (unsigned int j = 0; j < quantityAxes; j++)
			tempInit.push_back(dataSensorsInit[i][indxGyro + j]);
		for (unsigned int j = 0; j < quantityAxes - 1; j++)
			tempInit.push_back(dataSensorsInit[i][indxMagnet + j]);
		dataIMUInit.push_back(tempInit);
		tempInit.clear();
		dataTimeInit.push_back(dataSensorsInit[i][indxTime] / 1000);
		tempInit.clear();
	}
	meanGNSS = new double[quantityAxes];
	meanGNSS = accumulationPositionGNSS(dataInitGNSS);
	g = gravitationalAccelerationCalc(meanGNSS[0], meanGNSS[2]);
	#ifdef DEBUG
		vectPlot2d_t		plotAccelerationXYZFilter(quantityAxes);
		Plot				plotAccelerationVecXFilter;
		Plot				plotAccelerationVecYFilter;
		Plot				plotAccelerationVecZFilter;

		vectDouble_t		accelerationXFilter;
		vectDouble_t		accelerationYFilter;
		vectDouble_t		accelerationZFilter;

		for	(int i = 0; i < dataIMU.size(); i++)
		{
			accelerationXFilter.push_back(dataIMU[i][0]);
			accelerationYFilter.push_back(dataIMU[i][1]);
			accelerationZFilter.push_back(dataIMU[i][2]);
		}
		drawGraph(&dataTime, &accelerationXFilter, &plotAccelerationVecXFilter, "xAcceleration", 0);
		drawGraph(&dataTime, &accelerationYFilter, &plotAccelerationVecYFilter, "yAcceleration", 0);
		drawGraph(&dataTime, &accelerationZFilter, &plotAccelerationVecZFilter, "zAcceleration", 0);
		plotAccelerationVecXFilter.grid().show();
		plotAccelerationVecYFilter.grid().show();
		plotAccelerationVecZFilter.grid().show();
		plotAccelerationXYZFilter[0].push_back(plotAccelerationVecXFilter);
		plotAccelerationXYZFilter[1].push_back(plotAccelerationVecYFilter);
		plotAccelerationXYZFilter[2].push_back(plotAccelerationVecZFilter);
		Figure				figAccelerationFilter = plotAccelerationXYZFilter;
		figAccelerationFilter.size(600, 700);
		figAccelerationFilter.show();
		figAccelerationFilter.save("accelerationNoFilter.png");
	#endif
	getCorrectData(dataIMU, dataIMUInit, g);
	#ifdef DEBUG
		vectPlot2d_t		plotAccelerationXYZ(quantityAxes);
		Plot				plotAccelerationVecX;
		Plot				plotAccelerationVecY;
		Plot				plotAccelerationVecZ;

		vectDouble_t		accelerationX;
		vectDouble_t		accelerationY;
		vectDouble_t		accelerationZ;

		for	(int i = 0; i < dataIMU.size(); i++)
		{
			accelerationX.push_back(dataIMU[i][0]);
			accelerationY.push_back(dataIMU[i][1]);
			accelerationZ.push_back(dataIMU[i][2]);
		}
		drawGraph(&dataTime, &accelerationX, &plotAccelerationVecX, "xAcceleration", 0);
		drawGraph(&dataTime, &accelerationY, &plotAccelerationVecY, "yAcceleration", 0);
		drawGraph(&dataTime, &accelerationZ, &plotAccelerationVecZ, "zAcceleration", 0);
		plotAccelerationVecX.grid().show();
		plotAccelerationVecY.grid().show();
		plotAccelerationVecZ.grid().show();
		plotAccelerationXYZ[0].push_back(plotAccelerationVecX);
		plotAccelerationXYZ[1].push_back(plotAccelerationVecY);
		plotAccelerationXYZ[2].push_back(plotAccelerationVecZ);
		Figure				figAcceleration = plotAccelerationXYZ;
		figAcceleration.size(600, 700);
		figAcceleration.show();
		figAcceleration.save("acceleration.png");
	#endif
	positionWGS = estimatePositionWGS(&dataIMU, &dataGNSS, meanGNSS, &dataTime);
	delete[] meanGNSS;
	std::cout << "Широта в начальный момент времени\t= " << positionWGS[0][0] << std::endl;
	std::cout << "Долгота в начальный момент времени\t= " << positionWGS[0][1] << std::endl;
	std::cout << "Высота в начальный момент времени\t= " << positionWGS[0][2] << std::endl;
	std::cout << std::endl;
	std::cout << "Широта в конечный момент времени\t= " << positionWGS[positionWGS.size() - 10][0] << std::endl;
	std::cout << "Долгота в конечный момент времени\t= " << positionWGS[positionWGS.size() - 10][1] << std::endl;
	std::cout << "Высота в конечный момент времени\t= " << positionWGS[positionWGS.size() - 10][2] << std::endl;
	for	(unsigned int i = 0; i < positionWGS.size(); i++)
	{
		xPositionWGS.push_back(positionWGS[i][0]);
		yPositionWGS.push_back(positionWGS[i][1]);
		zPositionWGS.push_back(positionWGS[i][2]);
	}
	writeToFile(&positionWGS, "positionWGS");
	drawGraph(&dataTime, &xPositionWGS, &plotPositionX, "xPosition", 0);
	drawGraph(&dataTime, &yPositionWGS, &plotPositionY, "yPosition", 0);
	drawGraph(&dataTime, &zPositionWGS, &plotPositionZ, "zPosition", 0);
	plotPositionX.grid().show();
	plotPositionY.grid().show();
	plotPositionZ.grid().show();
	plotPositionXYZ[0].push_back(plotPositionX);
	plotPositionXYZ[1].push_back(plotPositionY);
	plotPositionXYZ[2].push_back(plotPositionZ);
	Figure				figPosition = plotPositionXYZ;
	figPosition.size(600, 600);
	figPosition.show();
}
