/* \file shader.h*/
#pragma once
#include <cstdint>
#include <glm/glm.hpp>

namespace Engine {
	
	/**\class Shader
	** \brief API Agnostic shader
	*/
	class Shader

	{
	public:

		virtual ~Shader() = default; //<! Destructor
		virtual uint32_t getID() const = 0; //!< Get the render ID
		virtual void uploadInt(const char* name, int value) = 0; //!< Upload an int to the shader 
		virtual void uploadFloat(const char* name, float value) = 0; //!< Upload a float to the shader
		virtual void uploadFloat2(const char* name, const glm::vec2& value) = 0;//!< Upload a float2 to the shader
		virtual void uploadFloat3(const char* name, const glm::vec3& value) = 0;//!< Upload a float3 to the shader
		virtual void uploadFloat4(const char* name, const glm::vec4& value) = 0;//!< Upload a float4 to the shader
		virtual void uploadMat4(const char* name, const glm::mat4& value) = 0;//!< Upload a mat4 to the shader

		static Shader* create(const char* vertexFilepath, const char* fragmentFilepath); //!< Create a vertex or a fragment shader
		static Shader* create(const char* filepath); //!< Create a shader using only filepath (a single shader file containing fragment, vertex, and other type of shaders)
	};
}