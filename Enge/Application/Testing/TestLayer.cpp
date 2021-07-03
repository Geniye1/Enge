#include "TestLayer.h"

namespace Enge {

	TestLayer::TestLayer(PerspectiveCameraController* perspectiveCameraCont)
		: Layer("TestLayer"), m_perspectiveCameraCont(perspectiveCameraCont)
	{

	}

	void TestLayer::OnStart() {

		vertices = {
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};

		m_EntityStack.PushEntity(new TestEntity("Test Entity", vertices));

		for (Entity* entity : m_EntityStack) {
			entity->InitRender();
			entity->OnStart();
		}

		unsigned int fbTexId = frameBuffer->CreateFramebuffer();

		ImGui3DViewport* viewport = new ImGui3DViewport(fbTexId);
		imGuiWindowManager->AddWindow(viewport);

		previousTime = glfwGetTime();
	}

	void TestLayer::OnEnd() {

	}

	void TestLayer::OnUpdate(float dt) {

		CalculateFPS();

		// Enable the framebuffer so that anything that gets rendered by the Entities is sent into the framebuffer
		frameBuffer->FirstPass();

		// View matrix to pass to each Entity for rendering
		m_perspectiveCameraCont->updateMouseLook();
		glm::mat4 viewMatrix = m_perspectiveCameraCont->updateCameraPosition(dt);

		for (Entity* entity : m_EntityStack) {
			entity->OnTick(dt);
			entity->Render(viewMatrix);
		}

		// Disable the framebuffer so any rendering isn't sent into it and then render the stored framebuffer to the quad that fits
		// to the screen
		frameBuffer->SecondPass();

		imGuiWindowManager->OnUpdate();
		imGuiWindowManager->Render();
	}

	void TestLayer::CalculateFPS() {
		double currentTime = glfwGetTime();
		frameCount++;

		if (currentTime - previousTime >= 1.0) {
			LOG(ENGE_DEBUG, "FPS: %i \n", frameCount);

			frameCount = 0;
			previousTime = currentTime;
		}
	}

}