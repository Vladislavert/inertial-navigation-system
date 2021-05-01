#include "draw.hpp"

/*
	построение графиков

	time 		- ось абсцисс
	data 		- ось ординат
	nameGraph	- наименование графика
	palette		- палитра
	lineWidth	- толщина линии
*/
void	drawGraph(Vec time, Vec data, std::string nameGraph, bool show, std::string palette, int lineWidth)
{
	Plot plot;
	    plot.legend()
        .atOutsideBottom()
        .displayHorizontal()
        .displayExpandWidthBy(2);
	plot.palette(palette);
	plot.drawCurve(time, data).label(nameGraph).lineWidth(lineWidth);
	// plot.drawCurve(time, data).lineWidth(lineWidth);

	if (show == true)
    	plot.show();
}

void	drawGraph(Vec time, Vec data, Plot *plot, std::string nameGraph, bool show, std::string palette, int lineWidth)
{
	(*plot).legend()
        .atOutsideBottom()
        .displayHorizontal()
        .displayExpandWidthBy(2);
	(*plot).palette(palette);
	(*plot).drawCurve(time, data).label(nameGraph).lineWidth(lineWidth);
	if (show == true)
    	(*plot).show();
}

void	drawLine(Vec time, double data, std::string nameGraph, bool show, std::string palette, int lineWidth)
{
	Plot plot;
	plot.legend()
        .atOutsideBottom()
        .displayHorizontal()
        .displayExpandWidthBy(2);
	plot.palette(palette);
	Vec x = {time[0], time[time.size() - 1]};
    Vec y = {data, data};
	plot.drawBrokenCurveWithPoints(x, y).label("broken lines");
	if (show == true)
    	plot.show();
}

void	drawLine(Vec time, double data, Plot *plot, std::string nameGraph, bool show, std::string palette, int lineWidth)
{
	(*plot).legend()
        .atOutsideBottom()
        .displayHorizontal()
        .displayExpandWidthBy(2);
	(*plot).palette(palette);
	Vec x = {time[0], time[time.size() - 1]};
    Vec y = {data, data};
	(*plot).drawCurve(x, y).label(nameGraph).lineWidth(lineWidth);
	if (show == true)
    	(*plot).show();
}