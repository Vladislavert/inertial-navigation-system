/* ************************************ */
/* 	|Author: Vladislavert              |*/
/* 	|e-mail: chuvarevanv@gmail.ru      |*/
/* 	|draw.hpp                          |*/
/*	|__________________________________|*/
/* ************************************ */

#ifndef INERTIAL_NAVIGATION_SYSTEM_DRAW_HPP_
#define INERTIAL_NAVIGATION_SYSTEM_DRAW_HPP_

#include "typesData.hpp"

void	drawGraph(const Vec *time, const Vec *data, const std::string& nameGraph = "graph",
				  bool show = true, int lineWidth = 2);
void	drawGraph(const vectDouble_t *time, const vectDouble_t *data, const std::string& nameGraph = "graph",
				  bool show = true, int lineWidth = 2);
void	drawGraph(const vectDouble_t *time, const vectDouble_t *data, Plot *plot,
				  const std::string& nameGraph = "graph", bool show = true,
				  const std::string& palette = "set1", int lineWidth = 2);
void	drawLine(const Vec *time, const double *data, const std::string& nameGraph = "graph", bool show = true,
				 const std::string& palette = "set1", int lineWidth = 2);
void	drawLine(const vectDouble_t *time, const double *data, Plot *plot, const std::string& nameGraph = "graph",
				 bool show = true, const std::string& palette = "set1", int lineWidth = 2);

#endif // INERTIAL_NAVIGATION_SYSTEM_DRAW_HPP_
