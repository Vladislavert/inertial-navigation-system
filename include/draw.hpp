#ifndef DRAW_HPP
#define DRAW_HPP

#include "typesData.hpp"

void	drawGraph(const Vec *time, const Vec *data, std::string nameGraph = "graph", bool show = true, std::string palette = "set1", int lineWidth = 2);
void	drawGraph(const Vec *time, const Vec *data, Plot *plot, std::string nameGraph = "graph", bool show = true, std::string palette = "set1", int lineWidth = 2);
void	drawLine(const Vec *time, const double *data, std::string nameGraph = "graph", bool show = true, std::string palette = "set1", int lineWidth = 2);
void	drawLine(const Vec *time, const double *data, Plot *plot, std::string nameGraph = "graph", bool show = true, std::string palette = "set1", int lineWidth = 2);

#endif