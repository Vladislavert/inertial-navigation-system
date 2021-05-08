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

#include "inputData.hpp"
#include "readFile.hpp"
#include "draw.hpp"
#include <../libraries/eigen3/Eigen/Dense>
#include "estimatePositionWGS.hpp"
#include "calcProbabilityCharact.hpp"
#include "initialExhibition.hpp"

// #define DEBUG

#ifdef DEBUG
	#include "iostream"
#endif

const unsigned int	indxGyro = 3; // значение индекса под которым начинаются измерения гироскопа
const unsigned int	indxMagnet = 6; // значение индекса под которым начинаются измерения магнитометра
const unsigned int	indxAcc = 0; // значение индекса под которым начинаются измерения акселерометра 
const unsigned int	indxTime = 12; // значение индекса под которым начинаются измерения времени
const unsigned int	indxOrient = 9; // значение индекса под которым начинаются измерения ориентации
// const unsigned int	indxGNSS = 9; // значение индекса под которым начинаются измерения позиции по ГНСС


int main()
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

	// nameFile = DIR_RESOURCES + "orientation360_2_chear (useful data).csv";
	nameFile = DIR_RESOURCES + "Move(orientation_30, 6 meters).csv";
	nameFileInitExhibition = DIR_RESOURCES + "InitCondition1.csv";
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
	vectDouble_t		temp; // временый вектор, для заполнения
	vectDouble_t		tempInit; // временый вектор, для заполнения данных начальной выставки

	for	(unsigned int i = 0; i < dataSensors.size(); i++)
	{
		for (unsigned int j = 0; j < 3; j++)
		{
			temp.push_back(dataSensors[i][indxAcc + j]);
			tempInit.push_back(dataSensorsInit[i][indxAcc + j]);
		}
		for (unsigned int j = 0; j < 3; j++)
		{
			temp.push_back(dataSensors[i][indxGyro + j]);
			tempInit.push_back(dataSensorsInit[i][indxGyro + j]);
		}
		for (unsigned int j = 0; j < 2; j++)
		{
			temp.push_back(dataSensors[i][indxMagnet + j]);
			tempInit.push_back(dataSensorsInit[i][indxMagnet + j]);
		}
		dataIMU.push_back(temp);
		dataIMUInit.push_back(tempInit);
		temp.clear();
		for (unsigned int j = 0; j < 3; j++)
			temp.push_back(0);
		dataGNSS.push_back(temp);
		dataTime.push_back(dataSensors[i][indxTime] / 1000);
		temp.clear();
	}
	#ifdef DEBUG
		vectDouble2d_t 		dataIMUTranspose(dataIMUInit[0].size()); // данные с БИНС(акселерометр(X, Y, Z), гироскоп(X, Y, Z), магнетометр(X, Y))
		meanAcc = new double[3];
		dispersionAcc = new double[3];
		meanGyro = new double[3];
		dispersionGyro = new double[3];

		for	(unsigned int i = 0; i < dataIMUInit[0].size(); i++)
		{
			for (unsigned int j = 0; j < dataIMUInit.size(); j++)
			{
				dataIMUTranspose[i].push_back(dataIMUInit[j][i]);
			}	
		}
		
		for	(unsigned int i = 0; i < 3; i++)
		{
			meanAcc[i] = meanCalculate(dataIMUTranspose[i]);
		}
		for	(unsigned int i = 0; i < 3; i++)
		{
			meanGyro[i] = meanCalculate(dataIMUTranspose[3 + i]);
		}
		for	(unsigned int i = 0; i < 3; i++)
		{
			dispersionAcc[i] = dispersionCalculate(dataIMUTranspose[i], meanAcc[i]);
			dispersionGyro[i] = dispersionCalculate(dataIMUTranspose[3 + i], meanGyro[i]);
		}
		for	(unsigned int i = 0; i < 3; i++)
		{
			std::cout << "value meanAcc[" << i << "] = " << meanAcc[i] << "\t| ";
			std::cout << "value meanGyro[" << i << "] = " << meanGyro[i] << "\t| ";
			std::cout << "value dispersionAcc[" << i << "] = " << meanAcc[i] << "\t| ";
			std::cout << "value dispersionGyro[" << i << "] = " << meanGyro[i] << "\t| ";
			std::cout << std::endl;
		}
	#endif
	getCorrectData(dataIMU, dataIMUInit);
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
	// drawGraph(&dataTime, &xPositionWGS, "xPosition");
	// drawGraph(&dataTime, &yPositionWGS, "yPosition");
	// drawGraph(&dataTime, &zPositionWGS, "zPosition");
}



