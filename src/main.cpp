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

#define DEBUG

#ifdef DEBUG
	#include "iostream"
#endif

#define DEBUG

using namespace Eigen;

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
	std::string			nameFile;
	vectString_t		str;
	vectDouble2d_t		dataSensors; // данные с датчиков
	vectDouble2d_t		positionWGS; // оценка позиции в WGS84(X, Y, Z)

	nameFile = DIR_RESOURCES + "orientation360_2_chear (useful data).csv";
	file.open(nameFile);
	if (checkOpenFile(file))
	{
		readStrFile(file, str);
		inputData(str, dataSensors, 1);
		file.close();
		str.clear();
	}
	else
		std::exit(0);
	// запись данных с сенсоров из общего вектора в вектор соответсвующие типу датчик
	vectDouble2d_t 		dataIMU; // данные с БИНС(акселерометр(X, Y, Z), гироскоп(X, Y, Z), магнетометр(X, Y))
	vectDouble2d_t		dataGNSS; // данные с ГНСС(широта, долгота, высота)
	vectDouble_t		dataTime; // время с начала замера данных с датчиков
	vectDouble_t		temp; // временый вектор, для заполнения

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
		dataTime.push_back(dataSensors[i][indxTime]);
		temp.clear();
	}
	estimatePositionWGS(&dataIMU, &dataGNSS, &dataTime);
}



