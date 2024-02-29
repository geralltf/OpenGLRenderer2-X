#include "Triangle.h"

Triangle::Triangle() : 
	positionXStep(Vector3f::ZERO),
	positionYStep(Vector3f::ZERO),
	colourXStep(Vector4f::ZERO),
	colourYStep(Vector4f::ZERO),
	normalXStep(Vector3f::ZERO),
	normalYStep(Vector3f::ZERO),
	texCoordXStep(new Vector2f(0.0f, 0.0f)),
	texCoordYStep(new Vector2f(0.0f, 0.0f)),
	Origin(Vector3f::ZERO),
	vertex00(Vector3f::ZERO),
	vertex01(Vector3f::ZERO),
	vertex10(Vector3f::ZERO),
	normal00(Nullable<Vector3f*>()),
	normal01(Nullable<Vector3f*>()),
	normal10(Nullable<Vector3f*>()),
	colour00(Nullable<Vector4f*>()),
	colour01(Nullable<Vector4f*>()),
	colour10(Nullable<Vector4f*>()),
	texCoord00(Nullable<Vector2f*>()),
	texCoord01(Nullable<Vector2f*>()),
	texCoord10(Nullable<Vector2f*>()),
	faceColour(Nullable<ColourRGBA*>())
{
	// Nothing to do here.
}

Triangle::Triangle(Vector3f* t0, Vector3f* t1, Vector3f* t2) :
	positionXStep(Vector3f::ZERO),
	positionYStep(Vector3f::ZERO),
	colourXStep(Vector4f::ZERO),
	colourYStep(Vector4f::ZERO),
	normalXStep(Vector3f::ZERO),
	normalYStep(Vector3f::ZERO),
	texCoordXStep(new Vector2f(0.0f, 0.0f)),
	texCoordYStep(new Vector2f(0.0f, 0.0f)),
	Origin(Vector3f::ZERO),
	vertex00(Vector3f::ZERO),
	vertex01(Vector3f::ZERO),
	vertex10(Vector3f::ZERO),
	normal00(Nullable<Vector3f*>()),
	normal01(Nullable<Vector3f*>()),
	normal10(Nullable<Vector3f*>()),
	colour00(Nullable<Vector4f*>()),
	colour01(Nullable<Vector4f*>()),
	colour10(Nullable<Vector4f*>()),
	texCoord00(Nullable<Vector2f*>()),
	texCoord01(Nullable<Vector2f*>()),
	texCoord10(Nullable<Vector2f*>()),
	faceColour(Nullable<ColourRGBA*>())
{
	vertex00 = t0;
	vertex01 = t1;
	vertex10 = t2;
}

Triangle::~Triangle()
{

}

Triangle* Triangle::Clone(Triangle* t) // BUG:HACK: Cloning triangle because coordinates seem to be weirdly affected by transformations
{
	Triangle* c = new Triangle(new Vector3f(t->vertex00->x, t->vertex00->y, t->vertex00->z),
		new Vector3f(t->vertex01->x, t->vertex01->y, t->vertex01->z),
		new Vector3f(t->vertex10->x, t->vertex10->y, t->vertex10->z));

	if (t->HasVertexNormals())
	{

		c->normal00 = new Vector3f(t->normal00.get()->x, t->normal00.get()->y, t->normal00.get()->z);
		c->normal01 = new Vector3f(t->normal01.get()->x, t->normal01.get()->y, t->normal01.get()->z);
		c->normal10 = new Vector3f(t->normal10.get()->x, t->normal10.get()->y, t->normal10.get()->z);
	}


	c->colour00 = t->colour00;
	c->colour01 = t->colour01;
	c->colour10 = t->colour10;

	c->texCoord00 = t->texCoord00;
	c->texCoord01 = t->texCoord01;
	c->texCoord10 = t->texCoord10;

	return c;
}


void Triangle::Grad()
{
	float minToMaxY = vertex00->y - vertex10->y;
	float midToMaxY = vertex01->y - vertex10->y;

	float minToMaxX = vertex00->x - vertex10->x;
	float midToMaxX = vertex01->x - vertex10->x;

	float oneOverdX = 1.0f / ((midToMaxX * minToMaxY) - (minToMaxX * midToMaxY));

	float oneOverdY = -oneOverdX;

	// Setup gradients for vertex attributes

	Vector3f* v0 = vertex00;
	Vector3f* v1 = vertex01;
	Vector3f* v2 = vertex10;

	Vector3f* left = Vector3f::Scale(Vector3f::Subtract(v1, v2), minToMaxY);
	Vector3f* right = Vector3f::Scale(Vector3f::Scale(Vector3f::Subtract(v0, v2), midToMaxY), oneOverdX);
	positionXStep = Vector3f::Subtract(left, right);

	Vector3f* left2 = Vector3f::Scale(Vector3f::Subtract(v1, v2), minToMaxX);
	Vector3f* right2 = Vector3f::Scale(Vector3f::Scale(Vector3f::Subtract(v0, v2), minToMaxX), oneOverdY);
	positionYStep = Vector3f::Subtract(left2, right2);


	if (HasVertexColours())
	{
		Vector4f* m0 = colour00.get();
		Vector4f* m1 = colour01.get();
		Vector4f* m2 = colour10.get();

		Vector4f* left3 = Vector4f::Scale(Vector4f::Subtract(m1, m2), minToMaxY);
		Vector4f* right3 = Vector4f::Scale(Vector4f::Scale(Vector4f::Subtract(m0, m2), midToMaxY), oneOverdX);
		colourXStep = Vector4f::Subtract(left3, right3);

		Vector4f* left4 = Vector4f::Scale(Vector4f::Subtract(m1, m2), minToMaxX);
		Vector4f* right4 = Vector4f::Scale(Vector4f::Scale(Vector4f::Subtract(m0, m2), midToMaxX), oneOverdY);
		colourYStep = Vector4f::Subtract(left4, right4);

		//colourXStep =
		//	(((m1 - m2) * minToMaxY) - ((m0 - m2) * midToMaxY)) * oneOverdX;

		//colourYStep =
		//	(((m1 - m2) * minToMaxX) - ((m0 - m2) * midToMaxX)) * oneOverdY;
	}

	if (HasVertexNormals())
	{
		Vector3f* m0 = normal00.get();
		Vector3f* m1 = normal01.get();
		Vector3f* m2 = normal10.get();

		Vector3f* left3 = Vector3f::Scale(Vector3f::Subtract(m1, m2), minToMaxY);
		Vector3f* right3 = Vector3f::Scale(Vector3f::Scale(Vector3f::Subtract(m0, m2), midToMaxY), oneOverdX);
		normalXStep = Vector3f::Subtract(left3, right3);

		Vector3f* left4 = Vector3f::Scale(Vector3f::Subtract(m1, m2), minToMaxX);
		Vector3f* right4 = Vector3f::Scale(Vector3f::Scale(Vector3f::Subtract(m0, m2), midToMaxX), oneOverdY);
		normalYStep = Vector3f::Subtract(left4, right4);

		//normalXStep =
		//	(((m1 - m2) * minToMaxY) - ((m0 - m2) * midToMaxY)) * oneOverdX;

		//normalYStep =
		//	(((m1 - m2) * minToMaxX) - ((m0 - m2) * midToMaxX)) * oneOverdY;
	}

	if (HasVertexTexCoords())
	{
		Vector2f* m0 = texCoord00.get();
		Vector2f* m1 = texCoord01.get();
		Vector2f* m2 = texCoord10.get();

		Vector2f* left3 = Vector2f::Scale(Vector2f::Subtract(m1, m2), minToMaxY);
		Vector2f* right3 = Vector2f::Scale(Vector2f::Scale(Vector2f::Subtract(m0, m2), midToMaxY), oneOverdX);
		texCoordXStep = Vector2f::Subtract(left3, right3);

		Vector2f* left4 = Vector2f::Scale(Vector2f::Subtract(m1, m2), minToMaxX);
		Vector2f* right4 = Vector2f::Scale(Vector2f::Scale(Vector2f::Subtract(m0, m2), midToMaxX), oneOverdY);
		texCoordYStep = Vector2f::Subtract(left4, right4);

		//texCoordXStep =
		//	(((m1 - m2) * minToMaxY) - ((m0 - m2) * midToMaxY)) * oneOverdX;

		//texCoordYStep =
		//	(((m1 - m2) * minToMaxX) - ((m0 - m2) * midToMaxX)) * oneOverdY;
	}
}

Vector3f* Triangle::TriangleLerp(Vector2f* uv)
{
	Vector3f* result = Vector3f::TriangleLerp(vertex00, vertex01, vertex10, uv->x, uv->y);
	return result;
}

Vector3f* Triangle::TriangleVertexLerp(Vector2f* uv)
{
	Vector3f* result = Vector3f::TriangleLerp(vertex00, vertex01, vertex10, uv->x, uv->y);
	return result;
}

Vector3f* Triangle::TriangleNormalLerp(Vector2f* uv) // if only!
{
	Vector3f* result = Vector3f::TriangleLerp(normal00.get(), normal01.get(), normal10.get(), uv->x, uv->y);
	return result;
}

Vector4f* Triangle::TriangleColourLerp(Vector2f* uv) // if only!
{
	Vector4f* result = Vector4f::TriangleLerp(colour00.get(), colour01.get(), colour10.get(), uv->x, uv->y);
	return result;
}

bool Triangle::HasVertexNormals()
{
	return normal00.is_set() && normal01.is_set() && normal10.is_set();
}

bool Triangle::HasVertexColours()
{
	return colour00.is_set() && colour01.is_set() && colour10.is_set();
}

bool Triangle::HasVertexTexCoords()
{
	return texCoord00.is_set() && texCoord01.is_set() && texCoord10.is_set();
}

Vector3f* Triangle::CenterOfTriangle()
{
	return Vector3f::Divide(Vector3f::Add(Vector3f::Add(vertex00, vertex01), vertex10), 3);
}

Vector3f* Triangle::GetNormal(Vector3f* vertexPosition)
{
	Vector3f* result = Vector3f::Subtract(vertexPosition, Origin);
	result = result->Normalised();
	return result;
}

Vector3f* Triangle::SurfaceNormal()
{
	Vector3f* u = Vector3f::Subtract(vertex01, vertex00);
	Vector3f* v = Vector3f::Subtract(vertex10, vertex01);
	Vector3f* normal = Vector3f::Cross(u, v);
	Vector3f* result = normal->Normalised();
	return result;
}

Vector3f* Triangle::SurfaceNormalFront() // Front face normal.
{
	Vector3f* edge1 = Vector3f::Subtract(vertex01, vertex00); // Opposite winding order, or opposite edge loop.
	Vector3f* edge2 = Vector3f::Subtract(vertex10, vertex01);
	Vector3f* result = Vector3f::Cross(edge1, edge2);
	result = result->Normalised();
	return result;
}

Vector3f* Triangle::SurfaceNormalBack() // Back face normal. (pointing in opposite direction)
{
	Vector3f* edge1 = Vector3f::Subtract(vertex01, vertex10); // Opposite winding order, or opposite edge loop.
	Vector3f* edge2 = Vector3f::Subtract(vertex00, vertex01);
	Vector3f* result = Vector3f::Cross(edge1, edge2);
	result = result->Normalised();
	return result;
}

void Triangle::SwapVectors()
{
	// Sort vertex atrributes by y-value.
	Vector3f* tmp;
	Vector4f* col;
	Vector3f* norm;
	Vector2f* tex;

	bool vc = HasVertexColours();
	bool vn = HasVertexNormals();
	bool vt = HasVertexTexCoords();

	if (vertex10->y < vertex01->y)
	{
		tmp = vertex10;
		vertex10 = vertex01;
		vertex01 = tmp;

		if (vc)
		{
			col = colour10.get();
			colour10 = colour01;
			colour01 = col;
		}

		if (vn)
		{
			norm = normal10.get();
			normal10 = normal01;
			normal01 = norm;
		}

		if (vt)
		{
			tex = texCoord10.get();
			texCoord10 = texCoord01;
			texCoord01 = tex;
		}
	}
	if (vertex01->y < vertex00->y)
	{
		tmp = vertex01;
		vertex01 = vertex00;
		vertex00 = tmp;

		if (vc)
		{
			col = colour01.get();
			colour01 = colour00;
			colour00 = col;
		}

		if (vn)
		{
			norm = normal01.get();
			normal01 = normal00;
			normal00 = norm;
		}

		if (vt)
		{
			tex = texCoord01.get();
			texCoord01 = texCoord00;
			texCoord00 = tex;
		}
	}
	if (vertex10->y < vertex01->y)
	{
		tmp = vertex10;
		vertex10 = vertex01;
		vertex01 = tmp;

		if (vc)
		{
			col = colour10.get();
			colour10 = colour01;
			colour01 = col;
		}

		if (vn)
		{
			norm = normal10.get();
			normal10 = normal01;
			normal01 = norm;
		}

		if (vt)
		{
			tex = texCoord10.get();
			texCoord10 = texCoord01;
			texCoord01 = tex;
		}
	}
}

float Triangle::GetArea()
{
	return TriangleAreaTimesTwo(vertex10->xy(), vertex01->xy(), vertex00->xy());
}
int Triangle::GetHandednessI()
{
	return GetArea() >= 0 ? 1 : 0;
}
bool Triangle::GetHandedness()
{
	return GetArea() >= 0;
}

float Triangle::TriangleAreaTimesTwo(Vector3f* b, Vector3f* c, Vector3f* m)
{
	Vector3f* d1 = Vector3f::Subtract(b, m);
	Vector3f* d2 = Vector3f::Subtract(c, m);

	return 0.5f * Vector3f::Crossf(d1, d2);
}

float Triangle::TriangleAreaTimesTwo(Vector2f* b, Vector2f* c, Vector2f* m)
{
	Vector2f* d1 = Vector2f::Subtract(b, m);
	Vector2f* d2 = Vector2f::Subtract(c, m);

	return 0.5f * Vector2f::Cross(d1, d2);
}
