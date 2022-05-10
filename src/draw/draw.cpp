/* ************************************ */
/* 	|Author: Vladislavert              |*/
/* 	|e-mail: chuvarevanv@gmail.ru      |*/
/* 	|draw.cpp                          |*/
/*	|__________________________________|*/
/* ************************************ */

#include "draw.hpp"

#include <utility>

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
void	drawGraph(const Vec *time, const Vec *data, const std::string& nameGraph, bool show, int lineWidth)
{
	Plot plot;
	plot.legend()
        .atOutsideBottom()
        .displayHorizontal()
        .displayExpandWidthBy(2);
	plot.drawCurve(*time, *data).label(nameGraph).lineWidth(lineWidth);
	if (show == true)
    	plot.show();
}

void	drawGraph(const vectDouble_t *time, const vectDouble_t *data, const std::string& nameGraph, bool show, int lineWidth)
{
	Plot plot;
	plot.legend()
        .atOutsideBottom()
        .displayHorizontal()
        .displayExpandWidthBy(2);
	plot.drawCurve(*time, *data).label(nameGraph).lineWidth(lineWidth);
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
void	drawGraph(const vectDouble_t *time, const vectDouble_t *data, Plot *plot, const std::string& nameGraph, bool show, const std::string& palette, int lineWidth)
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
void	drawLine(const Vec *time, const double *data, const std::string& nameGraph, bool show, const std::string& palette, int lineWidth)
{
	Plot plot;
	plot.legend()
        .atOutsideBottom()
        .displayHorizontal()
        .displayExpandWidthBy(2);
	plot.palette(palette);
	Vec x = {(*time)[0], (*time)[(*time).size() - 1]};
    Vec y = {*data, *data};
	plot.drawBrokenCurveWithPoints(x, y).label(nameGraph).lineWidth(lineWidth);
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
void	drawLine(const vectDouble_t *time, const double *data, Plot *plot, const std::string& nameGraph, bool show, const std::string& palette, int lineWidth)
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