#pragma once

#include "../Enge_PCH.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Application.h"
#include "../Shaders/Shader.h"

namespace Enge {

	class FrameBuffer {
	public:
		FrameBuffer() = default;
		~FrameBuffer() = default;

		void CreateFramebuffer();
		void InitalizeScreenQuad();
		void FirstPass();
		void SecondPass();
	private:
		unsigned int m_FrameBuffer = 0;
		unsigned int m_TextureColorBuffer = 0;
		unsigned int m_RenderBuffer = 0;

		unsigned int m_QuadVAO = 0;
		unsigned int m_QuadVBO = 0;

		Shader* m_FrameBufferShader = new Shader();
	};

}