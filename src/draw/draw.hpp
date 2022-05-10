/* ************************************ */
/* 	|Author: Vladislavert              |*/
/* 	|e-mail: chuvarevanv@gmail.ru      |*/
/* 	|draw.hpp                          |*/
/*	|__________________________________|*/
/* ************************************ */

#ifndef INERTIAL_NAVIGATION_SYSTEM_DRAW_HPP_
#define INERTIAL_NAVIGATION_SYSTEM_DRAW_HPP_

#include "typesData.hpp"

void	drawGraph(const Vec *time, const Vec *data, std::string nameGraph = "graph", bool show = true, int lineWidth = 2);
void	drawGraph(const vectDouble_t *time, const vectDouble_t *data, std::string nameGraph = "graph", bool show = true, int lineWidth = 2);
void	drawGraph(const vectDouble_t *time, const vectDouble_t *data, Plot *plot, std::string nameGraph = "graph", bool show = true, std::string palette = "set1", int lineWidth = 2);
void	drawLine(const Vec *time, const double *data, std::string nameGraph = "graph", bool show = true, std::string palette = "set1", int lineWidth = 2);
void	drawLine(const vectDouble_t *time, const double *data, Plot *plot, std::string nameGraph = "graph", bool show = true, std::string palette = "set1", int lineWidth = 2);

#endif // INERTIAL_NAVIGATION_SYSTEM_DRAW_HPP_
