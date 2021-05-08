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

#include "initialExhibition.hpp"

/**
 * @brief Корректирует данные с учётом математичесокго ожиание и дисперсии
 * 
 * @param dataIMU данные с БИНС(акселерометр(X, Y, Z), гироскоп(X, Y, Z), магнетометр(X, Y))
 * @param dataInitIMU данные с БИНС(акселерометр(X, Y, Z), гироскоп(X, Y, Z), магнетометр(X, Y)) для начальной выставки
 */
void	getCorrectData(vectDouble2d_t &dataIMU, const vectDouble2d_t &dataInitIMU)
{
	vectDouble2d_t 		dataIMUTranspose(dataInitIMU[0].size()); // данные с БИНС(акселерометр(X, Y, Z), гироскоп(X, Y, Z), магнетометр(X, Y))
	const unsigned int	indxGyro = 3; // значение индекса под которым начинаются измерения гироскопа
	const unsigned int	indxAcc = 0; // значение индекса под которым начинаются измерения акселерометра 
	double				*meanAcc;
	double				*dispersionAcc;
	double				*meanGyro;
	double				*dispersionGyro;

	meanAcc = new double[3];
	dispersionAcc = new double[3];
	meanGyro = new double[3];
	dispersionGyro = new double[3];
	for	(unsigned int i = 0; i < dataInitIMU[0].size(); i++)
		for (unsigned int j = 0; j < dataInitIMU.size(); j++)
			dataIMUTranspose[i].push_back(dataInitIMU[j][i]);
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
	for (unsigned int i = 0; i < dataIMU.size(); i++)
	{
		for (unsigned int j = 0; j < 3; j++)
		{
			dataIMU[i][j] = dataIMU[i][indxAcc + j] - meanAcc[j];
			dataIMU[i][j] = dataIMU[i][indxGyro + j] - meanGyro[j];
		}
	}
	
}