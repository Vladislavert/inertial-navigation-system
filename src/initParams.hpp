/* ************************************ */
/* 	|Author: Vladislavert              |*/
/* 	|e-mail: chuvarevanv@gmail.ru      |*/
/* 	|initParams.hpp                    |*/
/*	|__________________________________|*/
/* ************************************ */

#ifndef INERTIAL_NAVIGATION_SYSTEM_INIT_PARAMS_HPP_
#define	INERTIAL_NAVIGATION_SYSTEM_INIT_PARAMS_HPP_

const unsigned int	indxAcc = 0; // значение индекса под которым начинаются измерения акселерометра 
const unsigned int	indxGyro = 3; // значение индекса под которым начинаются измерения гироскопа
const unsigned int	indxMagnet = 6; // значение индекса под которым начинаются измерения магнитометра
const unsigned int	indxOrient = 9; // значение индекса под которым начинаются измерения ориентации
const unsigned int	indxTime = 16; // значение индекса под которым начинаются измерения времени
const unsigned int	indxGNSS = 12; // значение индекса под которым начинаются измерения позиции по ГНСС
const unsigned int	indxInitGNSS = 0; // значение для накопления позиции по ГНСС
const unsigned int	quantityAxes = 3; // количество осей по которым производятся измерения

#endif // INERTIAL_NAVIGATION_SYSTEM_INIT_PARAMS_HPP_
