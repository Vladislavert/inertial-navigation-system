#ifndef DRAW_HPP
#define DRAW_HPP

#include "typesData.hpp"

void	drawGraph(Vec time, Vec data, std::string nameGraph = "graph", bool show = true, std::string palette = "set1", int lineWidth = 2);
void	drawGraph(Vec time, Vec data, Plot *plot, std::string nameGraph = "graph", bool show = true, std::string palette = "set1", int lineWidth = 2);
void	drawLine(Vec time, double data, std::string nameGraph = "graph", bool show = true, std::string palette = "set1", int lineWidth = 2);
void	drawLine(Vec time, double data, Plot *plot, std::string nameGraph = "graph", bool show = true, std::string palette = "set1", int lineWidth = 2);

#endif