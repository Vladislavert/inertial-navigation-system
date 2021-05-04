#include "gravitationalAccelerationCalc.hpp"

/**
 * @brief расчёт ускорения свободного падения
 * 
 * @param phi - широта
 * @param h - высота
 * @return ускорение свободного падения
 */
double	gravitationalAccelerationCalc(double phi, double h)
{
	double g;

	g = g0 * (1 + 0.0053024 * squaring(std::sin(phi)) - 0.0000058 * squaring(std::sin(squaring(phi)))) - (3.686 / 1000000) * h;
	return (g);
}