#include "CharacterController.h"
#include <SFML/Window/Mouse.hpp>
#include <iostream>

void CharacterController::OnUpdate()
{
	dx = prevx - sf::Mouse::getPosition().x;
	dy = prevy - sf::Mouse::getPosition().y;

	prevx = sf::Mouse::getPosition().x;
	prevy = sf::Mouse::getPosition().y;
}

void CharacterController::OnFocus()
{
	PollInput();
}

void CharacterController::PollInput()
{
	direction = new Vector3f(0, 0, 0);
	rotation = new Vector3f(0, 0, 0);
	modelRotation = new Vector3f(0, 0, 0);
	lightRotation = new Vector3f(0, 0, 0);
	lightDirection = new Vector3f(0, 0, 0);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		direction->x = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		direction->x = -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		direction->z = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		direction->z = -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		direction->y = -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		direction->y = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		direction->x = -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		direction->x = 1;
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		rotation->x = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		rotation->x = -1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
	{
		modelRotation->z = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	{
		modelRotation->z = -1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
	{
		modelRotation->y = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
	{
		modelRotation->y = -1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
	{
		modelRotation->x = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
	{
		modelRotation->x = -1;
	}

	// Light rotation
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
	{
		lightRotation->x = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
	{
		lightRotation->x = -1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
	{
		lightRotation->y = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
	{
		lightRotation->y = -1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		lightRotation->z = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		lightRotation->z = -1;
	}

	// Light direction
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
	{
		lightDirection->x = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
	{
		lightDirection->x = -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		lightDirection->y = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
	{
		lightDirection->y = -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		lightDirection->z = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		lightDirection->z = -1;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		cameraTransform->Rotate(dx * rotSpeed * 0.1f, 0, dy * rotSpeed * 0.1f);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle))
	{
		Vector3f* rot = new Vector3f(dx, 0, dy);

		Matrix4* rotMat = Quaternion::Euler(rot->x * rotSpeed, rot->y * rotSpeed, rot->z * rotSpeed)->RotationMatrix();

		modelview = Matrix4::Multiply(modelview, rotMat);
	}

	movementSpeed = speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift))
	{
		movementSpeed = sprint;
	}

	cameraTransform->Rotate(rotation->x* rotSpeed, rotation->y* rotSpeed, rotation->z* rotSpeed);
	cameraTransform->Translate(Vector3f::Scale(direction, movementSpeed));
	worldPosition = Vector3f::Scale(direction, movementSpeed);

	modelview = Matrix4::Multiply(modelview, Quaternion::Euler(modelRotation->x * rotSpeed, modelRotation->y * rotSpeed, modelRotation->z * rotSpeed)->RotationMatrix());

	lightModelView->RotationYawPitchRoll(lightRotation->x * rotSpeed, lightRotation->y * rotSpeed, lightRotation->z * rotSpeed);
	lightModelView->Translate(Vector3f::Scale(lightDirection, speed));

	//Vector3 pos = cameraTransform.GetLocalPosition();
	//std::cout << "x: " << pos.x << " y: " << pos.y << " z: " << pos.z << " [" << rotation.x << ", " << rotation.y << ", " << rotation.z << "]" << std::endl;
}
