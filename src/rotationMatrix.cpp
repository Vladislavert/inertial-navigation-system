/* *************************************************************************************************** */
/* 	|Author: Vladislavert              |sssssssssso++——+++osssssssssssssssssssssssssssssssssssssssss|  */
/* 	|e-mail: chuvarevan@mail.ru        |oooooo..   /   |    ./yyyyyyyyyyosshhhhhyyyyyyyyyyyyyyyyyyyy|  */
/* 	|rotationMatrix.cpp                |yysssso////  /syyyyyyyyyyyyyyy0    /yhhhhhyyyyyyyyyyyyyyyyyy|  */
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

#include "rotationMatrix.hpp"

/**
 * @brief Вычисление матрицы поворотов
 * 
 * @param ang углы ориентации(кен, тангаж, рысканье)
 * @return матрица поворотов
 */
Eigen::Matrix3d	rotationMatrix(const vectDouble_t &ang)
{
	Eigen::Matrix3d R;

	// R << 	c(ang[2])*c(ang[1]), 												-c(ang[1])*s(ang[2]), 									s(ang[1]),
	// 		s(ang[0])*s(ang[1])*c(ang[2]) - c(ang[0])*s(ang[2]),			-s(ang[0])*s(ang[1])*s(ang[2]) + c(ang[0])*c(ang[2]),	s(ang[0])*c(ang[1]),
	// 		-c(ang[0])*sin(ang[1])*cos(ang[2])+sin(ang[0])*sin(ang[2]),	c(ang[0])*s(ang[1])*s(ang[2]) + s(ang[0])*c(ang[2]),	c(ang[0])*c(ang[1]);
	R << 	c(ang[1])*c(ang[2]),	s(ang[0])*s(ang[1])*c(ang[2]) - c(ang[0])*s(ang[2]),	c(ang[0])*sin(ang[1])*cos(ang[2])+sin(ang[0])*sin(ang[2]),
			c(ang[1])*s(ang[2]),	s(ang[0])*s(ang[1])*s(ang[2]) + c(ang[0])*c(ang[2]),	c(ang[0])*s(ang[1])*s(ang[2]) + s(ang[0])*c(ang[2]),
			-s(ang[1]),				s(ang[0])*c(ang[1]),									c(ang[0])*c(ang[1]);
	return (R);
}

/**
 * @brief функция для нахождения косинуса
 * 
 * @param angl угол в радианах
 * @return значение косинуса
 */
double			c(const double angl)
{
	return (cos(angl));
}

/**
 * @brief функция для нахождения синуса
 * 
 * @param angl угол в радианах
 * @return значение синуса
 */
double			s(const double angl)
{
	return (sin(angl));
}