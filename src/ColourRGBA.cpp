#include "ColourRGBA.h"

ColourRGBA::ColourRGBA()
{
	r = 0.0f;
	g = 0.0f;
	b = 0.0f;
}

ColourRGBA::ColourRGBA(Vector3f* v)
{
	r = v->x;
	g = v->y;
	b = v->z;
}

ColourRGBA::ColourRGBA(Vector4f* v)
{
	r = v->x;
	g = v->y;
	b = v->z;
	a = v->w;
}

Vector3f* ColourRGBA::GetHSV()
{
	return Colour::ToHSV(this);
}

void ColourRGBA::FromHSV(Vector3f* colour)
{
	ColourRGBA* newValue = Colour::FromHSV(colour);
	a = newValue->a;
	r = newValue->r;
	g = newValue->g;
	b = newValue->b;
}


ColourRGBA::ColourRGBA(byte alpha, byte red, byte green, byte blue)
{
	r = red / 255.0f;
	g = green / 255.0f;
	b = blue / 255.0f;
	a = alpha / 255.0f;
}

ColourRGBA::ColourRGBA(float alpha, float red, float green, float blue)
{
	r = red;
	g = green;
	b = blue;
	a = alpha;
}

byte* ColourRGBA::ToBytes()
{
	byte* bytes = new byte[4]{
		(byte)(a * 255),
		(byte)(r * 255),
		(byte)(g * 255),
		(byte)(b * 255)
	};

	return bytes;
}

Vector4f* ColourRGBA::ToVec4()
{
	return new Vector4f(a, r, g, b);
}

byte* ColourRGBA::ToBGRA() const
{
	byte* bytes = new byte[4]{
		(byte)(b * 255),
		(byte)(g * 255),
		(byte)(r * 255),
		(byte)(a * 255)
	};

	return bytes;
}


ColourRGBA* ColourRGBA::FromBytes(byte a, byte r, byte g, byte b)
{
	return new ColourRGBA(a / 255.0f, r / 255.0f, g / 255.0f, b / 255.0f);
}

ColourRGBA* ColourRGBA::FromFloats(float a, float r, float g, float b)
{
	return new ColourRGBA(a, r, g, b);
}

Vector3f* ColourRGBA::ConvertToHSV(ColourRGBA* colour)
{
	return Colour::ToHSV(colour);
}
ColourRGBA* ColourRGBA::ConvertFromHSV(Vector3f* hsv)
{
	return Colour::FromHSV(hsv);
}

ColourRGBA* ColourRGBA::Divide(ColourRGBA* c, float denominator)
{
	return new ColourRGBA(c->a, c->r / denominator, c->g / denominator, c->b / denominator);
}

ColourRGBA* ColourRGBA::Scale(ColourRGBA* c, float scalar)
{
	return new ColourRGBA(c->a, c->r * scalar, c->g * scalar, c->b * scalar);
}

ColourRGBA* ColourRGBA::Add(ColourRGBA* left, float right)
{
    return new ColourRGBA(left->a, left->r + right, left->g * right, left->b * right);
}

ColourRGBA* ColourRGBA::Subtract(ColourRGBA* left, float right)
{
    return new ColourRGBA(left->a, left->r - right, left->g - right, left->b - right);
}

// ColourRGBA Operators
ColourRGBA* operator +=(ColourRGBA left, Vector3f* right)
{
	ColourRGBA* result = new ColourRGBA(left.r, left.g, left.b, left.a);
	result->r += right->x;
	result->g += right->y;
	result->b += right->z;
	return result;
}