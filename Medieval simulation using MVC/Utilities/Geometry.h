#include <iostream>
#include <iomanip>

#ifndef HOMEWORK3_GEMOTRY_H
#define HOMEWORK3_GEMOTRY_H
#include "Geometry.h"

using namespace std;
// angle units conversion functions
double to_radians(double theta_d);
double to_degrees(double theta_r);

// class declarations
typedef struct Point {
	double x;
	double y;
	Point(double x, double y);
	Point();
	bool operator==(const Point & rhs) const;
    friend std::ostream & operator<<(std::ostream &os, Point const &p){
        os << std::fixed << setprecision(2) << "(" << p.x << ", " << p.y << ")";
        return os;
    }
} Point;

double getNorm(const Point & vector1, const Point & vector2);




typedef struct Cartesian_vector {
	Cartesian_vector(const struct Polar_vector & pv);
	Cartesian_vector();
	void operator=(const struct Polar_vector & pv);
	double delta_x;
	double delta_y;
} Cartesian_vector;

typedef struct Polar_vector {
	Polar_vector(const Cartesian_vector & cv);
	Polar_vector();
	void operator=(const Cartesian_vector & cv);
	double r;
	double theta;
} Polar_vector;

#endif //HOMEWORK3_GEMOTRY_H
