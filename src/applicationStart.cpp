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
	vectDouble2d_t		dataSensorsInit; // данные с датчиков во время начальной инициалзиации
	vectDouble2d_t		positionWGS; // оценка позиции в WGS84(X, Y, Z)
	vectDouble_t		xPositionWGS;
	vectDouble_t		yPositionWGS;
	vectDouble_t		zPositionWGS;
	vectPlot2d_t		plotPositionXYZ(3);
	Plot				plotPositionX;
	Plot				plotPositionY;
	Plot				plotPositionZ;
	double				g;
	double				*meanGNSS;

	// nameFile = DIR_RESOURCES + "orientation360_2_chear (useful data).csv";
	// nameFile = DIR_RESOURCES + "Move(orientation_30, 6 meters).csv";
	// nameFile = DIR_RESOURCES + "move_long_meters.csv";
	// добавить файл, который будет накапливать данные с ГНСС
	// nameFile = DIR_RESOURCES + "initCondition2.csv";
	// nameFile = DIR_RESOURCES + "RotationX_360.csv";
	nameFile = DIR_RESOURCES + "GNSSup_0.csv";
	nameFileInitGNSS = DIR_RESOURCES + "initGNSSup_0.csv";
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
	// запись данных с сенсоров из общего вектора в вектор соответсвующие типу датчик
	vectDouble2d_t 		dataIMU; // данные с БИНС(акселерометр(X, Y, Z), гироскоп(X, Y, Z), магнетометр(X, Y))
	vectDouble2d_t 		dataIMUInit; // данные с БИНС(акселерометр(X, Y, Z), гироскоп(X, Y, Z), магнетометр(X, Y)) для начальной выставки
	vectDouble2d_t		dataGNSS; // данные с ГНСС(широта, долгота, высота)
	vectDouble2d_t		dataInitGNSS; // данные с ГНСС(широта, долгота, высота)
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
			temp.push_back(dataSensors[i][indxGNSS + j]);
		dataGNSS.push_back(temp);
		dataTime.push_back(dataSensors[i][indxTime] / 1000);
		temp.clear();		
	}
	for	(unsigned int i = 0; i < dataFileInitGNSS.size(); i++)
	{	
		temp.clear();
		for (unsigned int j = 0; j < 3; j++)
			temp.push_back(dataFileInitGNSS[i][indxInitGNSS + j]);
		dataInitGNSS.push_back(temp);
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
	meanGNSS = new double[3];
	meanGNSS = accumulationPositionGNSS(dataInitGNSS);
	g = gravitationalAccelerationCalc(meanGNSS[0], meanGNSS[2]); // данные для начальной выставки
	getCorrectData(dataIMU, dataIMUInit, g);
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
