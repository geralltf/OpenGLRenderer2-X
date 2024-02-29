#include "HE_Vertex.h"

HE_Vertex::HE_Vertex()
{
	Attributes = new VertexAttributes();
}

HE_Vertex::HE_Vertex(int index)
{
	Index = index;
	Attributes->Vertex = Vector3f::ZERO;
	Edge = nullptr;
}

HE_Vertex::HE_Vertex(int index, Vector3f* vertexPosition)
{
	Index = index;
	Attributes->Vertex = vertexPosition;
	Edge = nullptr;
}

HE_Vertex::~HE_Vertex()
{
	delete Attributes;
}

bool HE_Vertex::Equals(HE_Vertex otherVertex) const
{
	return Attributes->Vertex == otherVertex.Attributes->Vertex;
}
