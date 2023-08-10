#include "Geometry.h"
#include <cmath>
#include <ctgmath>

const double pi = 2. * atan2(1., 0.);

double to_radians(double theta_d)
{
	return theta_d * pi / 180.0;
}

double to_degrees(double theta_r)
{
	return theta_r * 180.0 / pi;
}

double getNorm(const Point & vector1, const Point & vector2){

    return  sqrt( pow(vector1.x - vector2.x, 2) + pow(vector1.y - vector2.y, 2));
}
// construct a Cartesian_vector from a Polar_vector
Cartesian_vector::Cartesian_vector(const Polar_vector& pv) {
	delta_x = pv.r * cos(pv.theta);
	delta_y = pv.r * sin(pv.theta);
}

Cartesian_vector::Cartesian_vector()
{
	delta_x = 0.0;
	delta_y = 0.0;
}

void Cartesian_vector::operator=(const Polar_vector& pv)
{
	delta_x = pv.r * cos(pv.theta);
	delta_y = pv.r * sin(pv.theta);
}

// construct a Polar_vector from a Cartesian_vector
Polar_vector::Polar_vector(const Cartesian_vector& cv) {
	r = sqrt((cv.delta_x * cv.delta_x) + (cv.delta_y * cv.delta_y));
	/* atan2 will return a negative angle for Quadrant III, IV, must translate to I, II */
	theta = atan2(cv.delta_y, cv.delta_x);
	if (theta < 0.)
		theta = 2. * pi + theta; // normalize degree positive
}
Polar_vector::Polar_vector()
{
	r = 0.0;
	theta = 0.0;
}
void Polar_vector::operator=(const Cartesian_vector& cv)
{
	r = sqrt((cv.delta_x * cv.delta_x) + (cv.delta_y * cv.delta_y));
	/* atan2 will return a negative angle for Quadrant III, IV, must translate to I, II */
	theta = atan2(cv.delta_y, cv.delta_x);
	if (theta < 0.)
		theta = 2. * pi + theta; // normalize degree positive
}

Point::Point(double x, double y) : x(x), y(y)
{
}

Point::Point()
{
	x = 0.0;
	y = 0.0;
}


bool Point::operator==(const Point & rhs) const
{
	return x/10 == rhs.x && y/10 == rhs.y;
}
