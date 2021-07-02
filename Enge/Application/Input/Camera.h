#pragma once

#include "../Enge_PCH.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Enge {

	class Camera {
	public:
		Camera() = default;
		~Camera() = default;

		void MoveForward(float dt);
		void MoveBackward(float dt);
		void MoveLeft(float dt);
		void MoveRight(float dt);

		glm::mat4 GetLookAt();

		float m_movementSpeed = 2.0f;

		glm::vec3 m_cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 m_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	};

}