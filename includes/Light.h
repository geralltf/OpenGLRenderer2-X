#ifndef LIGHT_H
#define LIGHT_H

#include "Vector3f.h"
#include "ColourRGBA.h"

class Light
{
public:
	Vector3f* position;
	ColourRGBA* colour;
	// TODO: type directional, point, spotlight
};

#endif