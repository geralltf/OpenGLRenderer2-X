#include "Colour.h"
#include "MathHelpers.h"

ColourRGBA* Colour::red = new ColourRGBA(1.0f, 1.0f, 0.0f, 0.0f);
ColourRGBA* Colour::green = new ColourRGBA(1.0f, 0.0f, 1.0f, 0.0f);
ColourRGBA* Colour::blue = new ColourRGBA(1.0f, 0.0f, 0.0f, 1.0f);
ColourRGBA* Colour::cyan = new ColourRGBA(1.0f, 0.0f, 1.0f, 1.0f);
ColourRGBA* Colour::black = new ColourRGBA(1.0f, 0.0f, 0.0f, 0.0f);
ColourRGBA* Colour::yellow = new ColourRGBA(1.0f, 1.0f, 0.92f, 0.016f);
ColourRGBA* Colour::magenta = new ColourRGBA(1.0f, 0.0f, 1.0f, 1.0f);
ColourRGBA* Colour::gray = new ColourRGBA(1.0f, 0.5f, 0.5f, 0.5f);
ColourRGBA* Colour::white = new ColourRGBA(1.0f, 1.0f, 1.0f, 1.0f);
ColourRGBA* Colour::clear = new ColourRGBA(0.0f, 0.0f, 0.0f, 0.0f);
ColourRGBA* Colour::grey = new ColourRGBA(1.0f, 0.5f, 0.5f, 0.5f);

ColourRGBA* Colour::Randomise()
{

	return new ColourRGBA(1.0f,
		ClampF((rand() * 100000.0f) / 100000.0f, 0.5f, 1),
		ClampF((rand() * 100000.0f) / 100000.0f, 0.5f, 1),
		ClampF((rand() * 100000.0f) / 100000.0f, 0.5f, 1)
	);
}

Vector3f* Colour::ToHSV(ColourRGBA* colour)
{
	float hue; // in degrees
	float saturation;
	float value;
	byte max = std::max(colour->r, std::max(colour->g, colour->b));
	byte min = std::min(colour->r, std::min(colour->g, colour->b));
	int delta = max - min;

	if (delta == 0) delta = 1;

	if (max == 0)
	{
		value = max;
		hue = -1;
		saturation = 0;
	}
	else
	{
		// Assign a hue to the primary colour present. 
		if (colour->r == max)
		{
			// between yellow & magenta
			hue = (colour->g - colour->b) / delta;
		}
		else if (colour->g == max)
		{
			// between cyan & yellow
			hue = 2 + (colour->b - colour->r) / delta;
		}
		else
		{
			// between magenta & cyan
			hue = 4 + (colour->r - colour->g) / delta;
		}
		hue *= 60;
		if (hue < 0)
		{
			hue += 360;
		}
		saturation = (max == 0) ? 0 : 1.0f - (1.0f * min / max);
		value = max / 255.0f;

		hue /= 360; // Normalise between 0 and 1.
	}
	return new Vector3f(hue, saturation, value);
}

ColourRGBA* Colour::FromHSV(Vector3f* hsvColour)
{
	return FromHSV(hsvColour->x, hsvColour->y, hsvColour->z);
}

ColourRGBA* Colour::FromHSV(float hue, byte saturation, byte value)
{
	float hueDegrees = hue * 360;
	int hi = (int)(std::floor(hueDegrees / 60)) % 6;
	float f = (float)(hueDegrees / 60 - std::floor(hueDegrees / 60));

	byte v = (byte)(ClampF(value, 0, 255));
	byte p = (byte)(ClampF(value * (1 - saturation), 0, 255));
	byte q = (byte)(ClampF(value * (1 - f * saturation), 0, 255));
	byte t = (byte)(ClampF(value * (1 - (1 - f) * saturation), 0, 255));

	if (hi == 0)
		return ColourRGBA::FromBytes(255, v, t, p);
	else if (hi == 1)
		return ColourRGBA::FromBytes(255, q, v, p);
	else if (hi == 2)
		return ColourRGBA::FromBytes(255, p, v, t);
	else if (hi == 3)
		return ColourRGBA::FromBytes(255, p, q, v);
	else if (hi == 4)
		return ColourRGBA::FromBytes(255, t, p, v);
	else
		return ColourRGBA::FromBytes(255, v, p, q);
}

ColourRGBA* Colour::FromHSV(float hue, float saturation, float value)
{
	float hueDegrees = hue * 360;
	int hi = (int)(std::floor(hueDegrees / 60)) % 6;
	float f = (float)(hueDegrees / 60 - std::floor(hueDegrees / 60));

	value = value * 255;
	//saturation = saturation * 255;
	byte v = (byte)(ClampF(value, 0, 255));
	byte p = (byte)(ClampF(value * (1 - saturation), 0, 255));
	byte q = (byte)(ClampF(value * (1 - f * saturation), 0, 255));
	byte t = (byte)(ClampF(value * (1 - (1 - f) * saturation), 0, 255));

	if (hi == 0)
		return ColourRGBA::FromBytes(255, v, t, p);
	else if (hi == 1)
		return ColourRGBA::FromBytes(255, q, v, p);
	else if (hi == 2)
		return ColourRGBA::FromBytes(255, p, v, t);
	else if (hi == 3)
		return ColourRGBA::FromBytes(255, p, q, v);
	else if (hi == 4)
		return ColourRGBA::FromBytes(255, t, p, v);
	else
		return ColourRGBA::FromBytes(255, v, p, q);
}