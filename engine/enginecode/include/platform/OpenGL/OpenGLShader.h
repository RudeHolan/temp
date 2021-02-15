/* \file OpenGLShader.h*/
#pragma once

#include "rendering/shader.h"


namespace Engine{

	/**\class OpenGLShader
	** \brief This class creates an OpenGL shader
	*/
	class OpenGLShader : public Shader
	{
	private:
		uint32_t m_OpenGL_ID;
		void compileAndLink(const char* vertexShaderSrc, const char* fragmentShaderSrc);

	public:
		OpenGLShader(const char* vertexFilepath, const char* fragmentFilepath); //!< Constructor
		OpenGLShader(const char* filepath); //!< Second constructor
		~OpenGLShader(); //!< Destructor
		uint32_t getID() const override { return m_OpenGL_ID; } //!< Get the render ID

		void uploadInt(const char* name, int value) override; //!< Upload an int to the shader
		void uploadIntArray(const char* name, int32_t* values, uint32_t count) override;
		void uploadFloat(const char* name, float value) override; //!< Upload an float to the shader
		void uploadFloat2(const char* name, const glm::vec2& value) override; //!< Upload a float2 to the shader
		void uploadFloat3(const char* name, const glm::vec3& value) override; //!< Upload a float3 to the shader
		void uploadFloat4(const char* name, const glm::vec4& value) override; //!< Upload a float4 to the shader
		void uploadMat4(const char* name, const glm::mat4& value) override; //!< Upload a mat4 to the shader

	};
}