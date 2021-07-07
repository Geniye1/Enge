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

		imGuiWindowManager->StartEditor(glfwGetCurrentContext(), fbTexId);

		previousTime = glfwGetTime();
	}

	void TestLayer::OnEnd() {

	}

	void TestLayer::OnUpdate(float dt) {

		CalculateFPS();

		// Enable the framebuffer so that anything that gets rendered by the Entities is sent into the framebuffer
		frameBuffer->FirstPass();
		
		bool isInteractingWithViewport = imGuiWindowManager->IsInteractingWithViewport();
		
		// View matrix to pass to each Entity for rendering (updated only when pressing LMousebutton
		if (Input::GetMouseButtonDown(GLFW_MOUSE_BUTTON_1) && isInteractingWithViewport) {
			glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

			if (!isClickedIn) {
				glfwSetCursorPos(glfwGetCurrentContext(), WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
				isClickedIn = true;
			}

			m_perspectiveCameraCont->updateMouseLook();
			viewMatrix = m_perspectiveCameraCont->updateCameraPosition(dt);

			for (Entity* entity : m_EntityStack) {
				entity->OnTick(dt);
				entity->Render(viewMatrix);
			}
		}
		else {
			isClickedIn = false;
			m_perspectiveCameraCont->IsFirstMouse();
			glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

			for (Entity* entity : m_EntityStack) {
				entity->OnTick(dt);
				entity->Render();
			}
		}
		

		// Disable the framebuffer so any rendering isn't sent into it and then render the stored framebuffer to the quad that fits
		// to the ImGui window
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