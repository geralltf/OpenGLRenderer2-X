#ifndef CHARACTER_CONTROLLER_H
#define CHARACTER_CONTROLLER_H

#include "Vector3f.h"
#include <SFML/Window/Keyboard.hpp>
#include "Transform.h"

class CharacterController
{
public:

	Vector3f*				lightRotation		= Vector3f::ZERO;
	Vector3f*				lightDirection		= Vector3f::ZERO;
	Vector3f*				modelRotation		= Vector3f::ZERO;
	Vector3f*				cursorForward		= Vector3f::ZERO;
	Vector3f*				direction			= Vector3f::ZERO;
	Vector3f*				rotation			= Vector3f::ZERO;
	Vector3f*				camera_pos			= Vector3f::ZERO;
	float					camera_angle_pitch	= 0.0f;
	float					camera_angle_yaw	= 0.0f;
	float					camera_angle_roll	= 0.0f;
	Vector3f*				camera_front		= new Vector3f(0.0f, 0.0f, 1.0f);
	Vector3f*				camera_up			= new Vector3f(0.0f, 1.0f, 0.0f);
	float					turnSpeed			= 0.1f;
	float					camera_speed		= 0.1f;
	float					movementSpeed		= 0;
	float					sprint				= 0.7f;
	float					speed				= 0.1f;
	float					rotSpeed			= 1.5f;
	Vector3f*				worldPosition		= Vector3f::ZERO;

	Transform*				cameraTransform		= new Transform();
	Matrix4*				modelview			= Matrix4::Identity();
	Matrix4*				lightModelView		= Matrix4::Identity();
	int					prevx = 0;
	int					prevy = 0;
	int					dx;
	int					dy;

	void OnUpdate();
	void OnFocus();

private:
	void PollInput();

};

#endif