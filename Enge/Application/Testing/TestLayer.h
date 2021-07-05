#pragma once

#include "../Enge_PCH.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../ThirdPartyHelpers/stb_image.h"

// Put Input in the PCH when you implement all the events
#include "../Input/Input.h"

#include "../Layers/Layer.h"
#include "../Shaders/Shader.h"
#include "../Renderer/FrameBuffer.h"
#include "../EntityStack.h"
#include "../Testing/TestEntity.h"
#include "../Application.h"
#include "../Input/PerspectiveCameraController.h"

#include "../ImGui/ImGuiEditorManager.h"
#include "../ImGui/Editor/ImGui3DViewport.h"
#include "../ImGui/Editor/ImGuiPropertiesPanel.h"

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
		glm::mat4 viewMatrix = glm::mat4(1.0f);

		bool isClickedIn = false;

		PerspectiveCameraController* m_perspectiveCameraCont;

		ImGuiEditorManager* imGuiWindowManager = new ImGuiEditorManager(glfwGetCurrentContext());

		double previousTime = 0;
		int frameCount = 0;
	};

}