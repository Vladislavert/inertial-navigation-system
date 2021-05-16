/* *************************************************************************************************** */
/* 	|Author: Vladislavert              |sssssssssso++——+++osssssssssssssssssssssssssssssssssssssssss|  */
/* 	|e-mail: chuvarevan@mail.ru        |oooooo..   /   |    ./yyyyyyyyyyosshhhhhyyyyyyyyyyyyyyyyyyyy|  */
/* 	|coordinateTransform.cpp           |yysssso////  /syyyyyyyyyyyyyyy0    /yhhhhhyyyyyyyyyyyyyyyyyy|  */
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

#include "coordinateTransform.hpp"

/**
 * @brief перевод из эллипсоидальной геоцентрической СК(ГСК) в прямоугольную ГСК
 * 
 * @param coordinateGeoElipse координаты в эллипсоидальной ГСК(B - широта, L - долгота, H - высота)
 * @return координаты в прямоугольной ГСК(X, Y, Z)
 */
vectDouble_t	convertGeoElipseToGeoNormal(const vectDouble_t *coordinateGeoElipse)
{
	vectDouble_t	coordinateGeoNormal((*coordinateGeoElipse).size());
	double			N; // радиус кривизны первого вертикала
	double			radLatitude; // широта
	double			radLongtitude; // долгота

	radLatitude = degToRad((*coordinateGeoElipse)[0]);
	radLongtitude = degToRad((*coordinateGeoElipse)[1]);
	N = a / sqrt((1 - squaring(e) * squaring(sin((*coordinateGeoElipse)[0]))));
	coordinateGeoNormal[0] = (N + (*coordinateGeoElipse)[2]) * cos(radLatitude) * cos(radLongtitude);
	coordinateGeoNormal[1] = (N + (*coordinateGeoElipse)[2]) * cos(radLatitude) * sin(radLongtitude);
	coordinateGeoNormal[2] = ((squaring(b)/squaring(a)) * N + (*coordinateGeoElipse)[2]) * sin(radLongtitude);
	// coordinateGeoNormal[2] = ((squaring(b)/squaring(a)) * N + (*coordinateGeoElipse)[2] - N * squaring(e)) * sin(radLongtitude);
	return (coordinateGeoNormal);
}

/**
 * @brief перевод из прямоугольной геоцентрической СК(ГСК) в эллипсоидальную ГСК
 * 
 * @param coordinateGeoNormal координаты в прямоугольной ГСК(X, Y, Z)
 * @return координаты в эллипсоидальной ГСК(B - широта, L - долгота, H - высота)
 */
vectDouble_t	convertGeoNormalToGeoElipse(const vectDouble_t *coordinateGeoNormal)
{
	vectDouble_t	coordinateGeoElipse((*coordinateGeoNormal).size());
	// double			Q; // радиус

	// coordinateGeoElipse[1] = atan((*coordinateGeoNormal)[1] / (*coordinateGeoNormal)[0]);
	// Q = (*coordinateGeoNormal)[0] * cos(coordinateGeoElipse[1]) + (*coordinateGeoNormal)[1] * sin(coordinateGeoElipse[1]);

	return (coordinateGeoElipse);
}