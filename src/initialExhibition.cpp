/* *************************************************************************************************** */
/* 	|Author: Vladislavert              |sssssssssso++——+++osssssssssssssssssssssssssssssssssssssssss|  */
/* 	|e-mail: chuvarevan@mail.ru        |oooooo..   /   |    ./yyyyyyyyyyosshhhhhyyyyyyyyyyyyyyyyyyyy|  */
/* 	|initialExhibition.cpp             |yysssso////  /syyyyyyyyyyyyyyy0    /yhhhhhyyyyyyyyyyyyyyyyyy|  */
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

#include "initialExhibition.hpp"

/**
 * @brief Корректирует данные с учётом математичесокго ожиание и дисперсии
 * 
 * @param dataIMU данные с БИНС(акселерометр(X, Y, Z), гироскоп(X, Y, Z), магнетометр(X, Y))
 * @param dataInitIMU данные с БИНС(акселерометр(X, Y, Z), гироскоп(X, Y, Z), магнетометр(X, Y)) для начальной выставки
 * @param g ускорение свободного падения во время начальной выставки
 */
void	getCorrectData(vectDouble2d_t &dataIMU, const vectDouble2d_t &dataInitIMU, const double g)
{
	vectDouble2d_t 		dataIMUTranspose(dataInitIMU[0].size()); // данные с БИНС(акселерометр(X, Y, Z), гироскоп(X, Y, Z), магнетометр(X, Y))
	const unsigned int	indxGyro = 3; // значение индекса под которым начинаются измерения гироскопа
	const unsigned int	indxAcc = 0; // значение индекса под которым начинаются измерения акселерометра
	const unsigned int	quantityAxes = 3; // количество осей по которым производятся измерения
	double				*meanAcc; // математическое ожидание акселерометра по трём связанным осям
	double				*dispersionAcc; // дисперсия данных с акселерометра по трём связанным осям
	double				*threeCovAcc; // 3*sigma акселерометра по трём связанным осям
	double				*meanGyro; // математическое ожидание гироскопа по трём связанным осям
	double				*dispersionGyro; // дисперсия данных с гироскопа по трём связанным осям
	double				*threeCovGyro; // 3*sigma гироскопа по трём связанным осям
	double				valueInit; // Значение, которое присваивается при попадания в "мёртвую" зону 

	meanAcc = new double[quantityAxes];
	dispersionAcc = new double[quantityAxes];
	threeCovAcc = new double[quantityAxes];
	meanGyro = new double[quantityAxes];
	dispersionGyro = new double[quantityAxes];
	threeCovGyro = new double[quantityAxes];
	for	(unsigned int i = 0; i < dataInitIMU[0].size(); i++)
		for (unsigned int j = 0; j < dataInitIMU.size(); j++)
			dataIMUTranspose[i].push_back(dataInitIMU[j][i]);
	for	(unsigned int i = 0; i < quantityAxes; i++)
		meanAcc[i] = meanCalculate(dataIMUTranspose[indxAcc + i]);
	for	(unsigned int i = 0; i < quantityAxes; i++)
		meanGyro[i] = meanCalculate(dataIMUTranspose[indxGyro + i]);
	for	(unsigned int i = 0; i < quantityAxes; i++)
	{
		dispersionAcc[i] = dispersionCalculate(dataIMUTranspose[indxAcc + i], meanAcc[i]);
		dispersionGyro[i] = dispersionCalculate(dataIMUTranspose[indxGyro + i], meanGyro[i]);
	}
	for (unsigned int i = 0; i < quantityAxes; i++)
	{
		threeCovAcc[i] = 3 * sqrt(dispersionAcc[i]);
		threeCovGyro[i] = 3 * sqrt(dispersionGyro[i]);
	}
	for (unsigned int i = 0; i < dataIMU.size(); i++)
		for (unsigned int j = 0; j < quantityAxes; j++)
		{
			if (j == quantityAxes - 1)
			{
				dataIMU[i][indxAcc + j] = dataIMU[i][indxAcc + j] - (meanAcc[j] - g);
				valueInit = g;
			}
			else
			{
				dataIMU[i][indxAcc + j] = dataIMU[i][indxAcc + j] - meanAcc[j];
				valueInit = 0;
			}
			dataIMU[i][indxGyro + j] = dataIMU[i][indxGyro + j] - meanGyro[j];
			if (dataIMU[i][indxAcc + j] < (threeCovAcc[j] + valueInit) && dataIMU[i][indxAcc + j] > (-threeCovAcc[j] + valueInit))
				dataIMU[i][indxAcc + j] = valueInit;
			if (dataIMU[i][indxGyro + j] < (threeCovGyro[j] + valueInit) && dataIMU[i][indxGyro + j] > (-threeCovGyro[j] + valueInit))
				dataIMU[i][indxGyro + j] = valueInit;
		}
}

/**
 * @brief накопление позиции по ГНСС
 * 
 * @param dataInitGNSS данные с ГНСС приёмника
 * @return среднее значение широты, долготы, высоты
 */
double	*accumulationPositionGNSS(vectDouble2d_t &dataInitGNSS)
{
	double *meanResult;

	meanResult = new double[3];
	for (unsigned int i = 0; i < dataInitGNSS.size(); i++)
	{
		meanResult[0] += dataInitGNSS[i][0];
		meanResult[1] += dataInitGNSS[i][1];
		meanResult[2] += dataInitGNSS[i][2];
	}
	meanResult[0] /= dataInitGNSS.size();
	meanResult[1] /= dataInitGNSS.size();
	meanResult[2] /= dataInitGNSS.size();
	return (meanResult);
}
