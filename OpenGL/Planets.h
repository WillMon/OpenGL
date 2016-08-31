#ifndef PLANET
#define PLANET

#include <iostream>
#include "Application.h"

class Planet
{
public:
	Planet(vec3,mat4, int, int ,int);
	~Planet();	
	

private:
	vec3 Location;
	mat4 matrix;
	int radius, row, columes;

	
};

Planet::Planet(vec3 vec ,mat4 mat ,int rad,int r,int col)
{
	Location = vec;
	matrix = mat;
	radius = rad;
	row = r;
	columes = col;
}

Planet::~Planet()
{
}

#endif // !PLANET
