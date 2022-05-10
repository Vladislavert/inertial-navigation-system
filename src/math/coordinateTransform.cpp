/* ************************************ */
/* 	|Author: Vladislavert              |*/
/* 	|e-mail: chuvarevanv@gmail.ru      |*/
/* 	|coordinateTransform.cpp           |*/
/*	|__________________________________|*/
/* ************************************ */

#include "coordinateTransform.hpp"

/**
 * @brief перевод из эллипсоидальной геоцентрической СК(ГСК) в прямоугольную ГСК
 * 
 * @param coordinateGeoEllipse координаты в эллипсоидальной ГСК(B - широта, L - долгота, H - высота) [град]
 * @return координаты в прямоугольной ГСК(X, Y, Z)
 */
vectDouble_t	convertGeoEllipseToGeoNormal(const vectDouble_t *coordinateGeoEllipse)
{
	vectDouble_t	coordinateGeoNormal((*coordinateGeoEllipse).size());
	double			N; // радиус кривизны первого вертикала
	double			radLatitude; // широта
	double			radLongitude; // долгота

	radLatitude = degToRad((*coordinateGeoEllipse)[0]);
	radLongitude = degToRad((*coordinateGeoEllipse)[1]);
	N = a / sqrt((1 - squaring(e) * squaring(sin(radLatitude))));
	coordinateGeoNormal[0] = (N + (*coordinateGeoEllipse)[2]) * cos(radLatitude) * cos(radLongitude);
	coordinateGeoNormal[1] = (N + (*coordinateGeoEllipse)[2]) * cos(radLatitude) * sin(radLongitude);
	coordinateGeoNormal[2] = ((squaring(b)/squaring(a)) * N + (*coordinateGeoEllipse)[2]) * sin(radLatitude);
	return (coordinateGeoNormal);
}

/**
 * @brief перевод из эллипсоидальной геоцентрической СК(ГСК) в прямоугольную ГСК
 * 
 * @param coordinateGeoEllipse координаты в эллипсоидальной ГСК(B - широта, L - долгота, H - высота) [град]
 * @return координаты в прямоугольной ГСК(X, Y, Z)
 */
vectDouble_t	convertGeoEllipseToGeoNormal(const double *coordinateGeoEllipse)
{
	vectDouble_t	coordinateGeoNormal(3);
	double			N; // радиус кривизны первого вертикала
	double			radLatitude; // широта
	double			radLongitude; // долгота

	radLatitude = degToRad(coordinateGeoEllipse[0]);
	radLongitude = degToRad(coordinateGeoEllipse[1]);
	N = a / sqrt((1 - squaring(e) * squaring(sin(radLatitude))));
	coordinateGeoNormal[0] = (N + coordinateGeoEllipse[2]) * cos(radLatitude) * cos(radLongitude);
	coordinateGeoNormal[1] = (N + coordinateGeoEllipse[2]) * cos(radLatitude) * sin(radLongitude);
	coordinateGeoNormal[2] = ((squaring(b)/squaring(a)) * N + coordinateGeoEllipse[2]) * sin(radLatitude);
	return (coordinateGeoNormal);
}

/**
 * @brief перевод из прямоугольной геоцентрической СК(ГСК) в эллипсоидальную ГСК
 * 
 * @param coordinateGeoNormal координаты в прямоугольной ГСК(X, Y, Z)
 * @return координаты в эллипсоидальной ГСК(B - широта, L - долгота, H - высота) [град]
 */
vectDouble_t	convertGeoNormalToGeoEllipse(const vectDouble_t *coordinateGeoNormal)
{
	vectDouble_t	coordinateGeoEllipse((*coordinateGeoNormal).size());
	double			eFirstSquare; // квадрат первого эксцентриситета
	double			eSecondSquare; // квадрат второго эксцентриситета
	double			rSquare;
	double			r;
	double			eSquare;
	double			F;
	double			G;
	double			c;
	double			s;
	double			P;
	double			Q;
	double			r_0;
	double			tmp;
	double			U;
	double			V;
	double			z_0;

	eFirstSquare = 2 * f - squaring(f);
	eSecondSquare = f* (2- f) / (squaring(1 - f));
	rSquare = squaring((*coordinateGeoNormal)[0]) + squaring((*coordinateGeoNormal)[1]);
	r = sqrt(rSquare);
	eSquare = squaring(a) - squaring(b);
	F = 54 * squaring(b) * squaring((*coordinateGeoNormal)[2]);
	G = rSquare + (1 - eFirstSquare) * squaring((*coordinateGeoNormal)[2]) - eFirstSquare * eSquare;
	c = (squaring(eFirstSquare) * F * rSquare) / (squaring(G) * G);
	s = pow((1 + c + sqrt(squaring(c) + 2 * c)), 1/3);
	P = F / (3 * squaring(s + 1/s + 1) * squaring(G));
	Q = sqrt(1 + 2 * squaring(eFirstSquare) * P);
	r_0 = -(eFirstSquare * P * r) / (1 + Q) + sqrt((squaring(a)/2) * (1 + 1/Q) - ((1 - eFirstSquare) * P * squaring((*coordinateGeoNormal)[2]))/(Q * (1 + Q)) - P* rSquare/2);
	tmp = squaring(r - eFirstSquare*r_0);
	U = sqrt(tmp + squaring((*coordinateGeoNormal)[2]));
	V = sqrt(tmp + (1 - eFirstSquare) * squaring((*coordinateGeoNormal)[2]));
	z_0 = (squaring(b) * (*coordinateGeoNormal)[2]) / (a * V);
	// широта
	coordinateGeoEllipse[0] = radToDeg(atan(((*coordinateGeoNormal)[2] + eSecondSquare * z_0) / r));
	// долгота
	coordinateGeoEllipse[1] = radToDeg(atan2((*coordinateGeoNormal)[1], (*coordinateGeoNormal)[0]));
	// высота
	coordinateGeoEllipse[2] = U * (1 - squaring(b) / (a * V));
	return (coordinateGeoEllipse);
}

/**
 * @brief перевод из прямоугольной геоцентрической СК(ГСК) в эллипсоидальную ГСК
 * 
 * @param coordinateGeoNormal координаты в прямоугольной ГСК(X, Y, Z)
 * @return координаты в эллипсоидальной ГСК(B - широта, L - долгота, H - высота) [град]
 */
vectDouble_t	convertGeoNormalToGeoEllipse(const double *coordinateGeoNormal)
{
	vectDouble_t	coordinateGeoEllipse(3);
	double			eFirstSquare; // квадрат первого эксцентриситета
	double			eSecondSquare; // квадрат второго эксцентриситета
	double			rSquare;
	double			r;
	double			eSquare;
	double			F;
	double			G;
	double			c;
	double			s;
	double			P;
	double			Q;
	double			r_0;
	double			tmp;
	double			U;
	double			V;
	double			z_0;

	eFirstSquare = 2 * f - squaring(f);
	eSecondSquare = f* (2- f) / (squaring(1 - f));
	rSquare = squaring((coordinateGeoNormal[0]) + squaring(coordinateGeoNormal[1]));
	r = sqrt(rSquare);
	eSquare = squaring(a) - squaring(b);
	F = 54 * squaring(b) * squaring(coordinateGeoNormal[2]);
	G = rSquare + (1 - eFirstSquare) * squaring(coordinateGeoNormal[2]) - eFirstSquare * eSquare;
	c = (squaring(eFirstSquare) * F * rSquare) / (squaring(G) * G);
	s = pow((1 + c + sqrt(squaring(c) + 2 * c)), 1/3);
	P = F / (3 * squaring(s + 1/s + 1) * squaring(G));
	Q = sqrt(1 + 2 * squaring(eFirstSquare) * P);
	r_0 = -(eFirstSquare * P * r) / (1 + Q) + sqrt((squaring(a)/2) * (1 + 1/Q) - ((1 - eFirstSquare) * P * squaring(coordinateGeoNormal[2]))/(Q * (1 + Q)) - P* rSquare/2);
	tmp = squaring(r - eFirstSquare*r_0);
	U = sqrt(tmp + squaring(coordinateGeoNormal[2]));
	V = sqrt(tmp + (1 - eFirstSquare) * squaring(coordinateGeoNormal[2]));
	z_0 = (squaring(b) * coordinateGeoNormal[2]) / (a * V);
	// широта
	coordinateGeoEllipse[0] = radToDeg(atan((coordinateGeoNormal[2] + eSecondSquare * z_0) / r));
	// долгота
	coordinateGeoEllipse[1] = radToDeg(atan2(coordinateGeoNormal[1], coordinateGeoNormal[0]));
	// высота
	coordinateGeoEllipse[2] = U * (1 - squaring(b) / (a * V));
	return (coordinateGeoEllipse);
}
