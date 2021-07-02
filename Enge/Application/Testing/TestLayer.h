#pragma once

#include "../Enge_PCH.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../ThirdPartyHelpers/stb_image.h"

#include "../Layers/Layer.h"
#include "../Shaders/Shader.h"
#include "../Renderer/FrameBuffer.h"
#include "../EntityStack.h"
#include "../Testing/TestEntity.h"
#include "../Application.h"
#include "../Input/PerspectiveCameraController.h"

namespace Enge {

	class TestLayer : public Layer {
	public:
		TestLayer(PerspectiveCameraController* perspectiveCameraCont);
		virtual ~TestLayer() = default;

		virtual void OnStart() override;
		virtual void OnEnd() override;
		virtual void OnUpdate(float ft) override;

		void CalculateFPS();

	private:
		FrameBuffer* frameBuffer = new FrameBuffer();

		EntityStack m_EntityStack;

		std::vector<float> vertices;

		PerspectiveCameraController* m_perspectiveCameraCont;

		double previousTime = 0;
		int frameCount = 0;
	};

}