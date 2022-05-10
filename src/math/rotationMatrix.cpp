/* ************************************ */
/* 	|Author: Vladislavert              |*/
/* 	|e-mail: chuvarevanv@gmail.ru      |*/
/* 	|rotationMatrix.cpp                |*/
/*	|__________________________________|*/
/* ************************************ */

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