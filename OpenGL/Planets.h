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

Planet::Planet(vec3,mat4,int,int,int)
{

}

Planet::~Planet()
{
}

#endif // !PLANET
