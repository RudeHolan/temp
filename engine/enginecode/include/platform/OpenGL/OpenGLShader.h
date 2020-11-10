/* \file OpenGLShader.h*/
#pragma once
#include <cstdint>
#include <glm/glm.hpp>

namespace Engine{
	class OpenGLShader
	{
	private:
		uint32_t m_OpenGL_ID;
		void compileAndLink(const char* vertexShaderSrc, const char* fragmentShaderSrc);

	public:
		OpenGLShader(const char* vertexFilepath, const char* fragmentFilepath);
		OpenGLShader(const char* filepath);
		~OpenGLShader();
		uint32_t getRenderID() const { return m_OpenGL_ID; }

		void uploadInt(const char* name, int value);
		void uploadFloat(const char* name, float value);
		void uploadFloat2(const char* name, glm::vec2& value);
		void uploadFloat3(const char* name, glm::vec3& value);
		void uploadFloat4(const char* name, glm::vec4& value);
		void uploadMat4(const char* name, glm::mat4& value);

	};
}