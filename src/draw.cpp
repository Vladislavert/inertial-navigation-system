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

#include "draw.hpp"

/**
 * @brief построение графиков по множеству точек
 * 
 * @param time ось абсцисс
 * @param data ось ординат
 * @param nameGraph наименование графика
 * @param show отрисовка графика(true - отрисовать; false - не отрисовывать)
 * @param palette палитра
 * @param lineWidth толщина линии
 */
void	drawGraph(const Vec *time, const Vec *data, std::string nameGraph, bool show, std::string palette, int lineWidth)
{
	Plot plot;
	// plot.xrange(0.0, (*time)[(*time).size() - 1]);
   	// plot.yrange(-0.1, 0.1);
	plot.legend()
        .atOutsideBottom()
        .displayHorizontal()
        .displayExpandWidthBy(2);
	// plot.palette(palette);
	// plot.size(600, 600);
	plot.drawCurve(*time, *data).label(nameGraph).lineWidth(lineWidth);
	// plot.drawCurve(time, data).lineWidth(lineWidth);

	if (show == true)
    	plot.show();
}

void	drawGraph(const vectDouble_t *time, const vectDouble_t *data, std::string nameGraph, bool show, std::string palette, int lineWidth)
{
	Plot plot;
	// plot.xrange(0.0, (*time)[(*time).size() - 1]);
   	// plot.yrange(-0.1, 0.1);
	plot.legend()
        .atOutsideBottom()
        .displayHorizontal()
        .displayExpandWidthBy(2);
	// plot.palette(palette);
	// plot.size(600, 600);
	plot.drawCurve(*time, *data).label(nameGraph).lineWidth(lineWidth);
	// plot.drawCurve(time, data).lineWidth(lineWidth);

	if (show == true)
    	plot.show();
}

/**
 * @brief построение графиков по множеству точек
 * 
 * @param time ось абсцисс
 * @param data ось ординат
 * @param plot полотно, на котром происходит отрисовка графика
 * @param nameGraph наименование графика
 * @param show отрисовка графика(true - отрисовать; false - не отрисовывать)
 * @param palette палитра
 * @param lineWidth толщина линии
 */
void	drawGraph(const Vec *time, const Vec *data, Plot *plot, std::string nameGraph, bool show, std::string palette, int lineWidth)
{
// 	(*plot).xrange(0.0, time[time.size() - 1]);
//    (*plot).yrange(-0.1, 0.1);
	(*plot).legend()
        .atOutsideBottom()
        .displayHorizontal()
        .displayExpandWidthBy(2);
	(*plot).palette(palette);
	(*plot).drawCurve(*time, *data).label(nameGraph).lineWidth(lineWidth);
	if (show == true)
    	(*plot).show();
}

/**
 * @brief построение линии по оси абсцисс
 * 
 * @param time ось абсцисс
 * @param data ось ординат
 * @param nameGraph наименование графика
 * @param show отрисовка графика(true - отрисовать; false - не отрисовывать)
 * @param palette палитра
 * @param lineWidth толщина линии
 */
void	drawLine(const Vec *time, const double *data, std::string nameGraph, bool show, std::string palette, int lineWidth)
{
	Plot plot;
	plot.legend()
        .atOutsideBottom()
        .displayHorizontal()
        .displayExpandWidthBy(2);
	plot.palette(palette);
	Vec x = {(*time)[0], (*time)[(*time).size() - 1]};
    Vec y = {*data, *data};
	plot.drawBrokenCurveWithPoints(x, y).label("broken lines");
	if (show == true)
    	plot.show();
}

/**
 * @brief построение линии по оси абсцисс
 * 
 * @param time ось абсцисс
 * @param data ось ординат
 * @param plot полотно, на котром происходит отрисовка графика
 * @param nameGraph наименование графика
 * @param show отрисовка графика(true - отрисовать; false - не отрисовывать)
 * @param palette палитра
 * @param lineWidth толщина линии
 */
void	drawLine(const Vec *time, const double *data, Plot *plot, std::string nameGraph, bool show, std::string palette, int lineWidth)
{
	(*plot).legend()
        .atOutsideBottom()
        .displayHorizontal()
        .displayExpandWidthBy(2);
	(*plot).palette(palette);
	Vec x = {(*time)[0], (*time)[(*time).size() - 1]};
    Vec y = {*data, *data};
	(*plot).drawCurve(x, y).label(nameGraph).lineWidth(lineWidth);
	if (show == true)
    	(*plot).show();
}