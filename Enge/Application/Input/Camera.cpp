#include "Camera.h"

namespace Enge {

	void Camera::MoveForward(float dt) {
		float adjustedCameraSpeed = m_currentSpeed * dt;

		m_cameraPos += adjustedCameraSpeed * m_cameraFront;
	}
	void Camera::MoveBackward(float dt) {
		float adjustedCameraSpeed = m_currentSpeed * dt;

		m_cameraPos -= adjustedCameraSpeed * m_cameraFront;
	}
	void Camera::MoveLeft(float dt) {
		float adjustedCameraSpeed = m_currentSpeed * dt;

		m_cameraPos -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * adjustedCameraSpeed;
	}
	void Camera::MoveRight(float dt) {
		float adjustedCameraSpeed = m_currentSpeed * dt;

		m_cameraPos += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * adjustedCameraSpeed;
	}

	void Camera::StartSprinting() {
		m_currentSpeed = m_sprintSpeed;
	}

	void Camera::StopSprinting() {
		m_currentSpeed = m_movementSpeed;
	}

	glm::mat4 Camera::GetLookAt() {
		glm::mat4 viewMatrix = glm::mat4(1.0f);
		viewMatrix = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);

		return viewMatrix;
	}
}