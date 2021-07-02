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
		void MoveUp(float dt);
		void MoveDown(float dt);

		void StartSprinting();
		void StopSprinting();

		glm::mat4 GetLookAt();

		glm::vec3 m_cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 m_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	private:
		float m_movementSpeed = 2.0f;
		float m_sprintSpeed = 6.0f;
		float m_currentSpeed = m_movementSpeed;

		// Rise_fall multiplier (used when floating up or down)
		float rfMultiplier = 3.0f;
	};

}