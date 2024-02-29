#ifndef AABB_H
#define AABB_H

#include "Vector3f.h"
#include "ColourRGBA.h"

class AABB
{
public:
	/// <summary>
	/// The center of the bounding box.
	/// </summary>
	Vector3f* Center;

	/// <summary>
	/// The half-size of the bounding box.
	/// </summary>
	Vector3f* HalfSize;

	/// <summary>
	/// The minimum of the bounding box.
	/// </summary>
	Vector3f* Min;

	/// <summary>
	/// The maximum of the bounding box.
	/// </summary>
	Vector3f* Max;

	AABB();
	AABB(Vector3f* center, Vector3f* halfSize);

	/// <summary>
	/// Get the center of the bounding box.
	/// </summary>
	Vector3f* GetCenter();

	/// <summary>
	/// Get the size of the bounding box.
	/// </summary>
	Vector3f* GetSize();

	/// <summary>
	/// Get the half size (radius vector) of the bounding box.
	/// </summary>
	Vector3f* GetHalfSize();

	/// <summary>
	/// The minimum extent of the bounding box.
	/// </summary>
	Vector3f* GetMin();

	/// <summary>
	/// The maximum extent of the bounding box.
	/// </summary>
	Vector3f* GetMax();

	/// <summary>
	/// Clears the AABB.
	/// </summary>
	void Empty();

	/// <summary>
	/// Add a point to the axis-aligned bounding box to compute the AABB.
	/// </summary>
	void Add(Vector3f* point);

	/// <summary>
	/// Add a bounding box to compute a greater AABB.
	/// </summary>
	void Add(AABB* boundingBox);

	/// <summary>
	/// Test if the specified point intersects this bounding box.
	/// </summary>
	bool Intersects(Vector3f* point);

	/// <summary>
	/// Test if the specified point intersects this bounding box.
	/// </summary>
	bool Intersects(Vector2f* point);

	/// <summary>
	/// Test if the specified bounding box intersects this bounding box.
	/// </summary>
	bool Intersects(AABB* other);

	/// <summary>
	/// Draws lines for each plane of the bounding box.
	/// </summary>
	void Debug(ColourRGBA* boundsColour = new ColourRGBA(1.0f, 0.0f, 0.0f, 1.0f));
};

#endif
