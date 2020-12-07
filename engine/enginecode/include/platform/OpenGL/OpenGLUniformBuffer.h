#pragma once
/*\file OpenGLUniformBuffer.h*/

#include "rendering/uniformBuffer.h"


namespace Engine
{

	/**\class OpenGLUniformBuffer
	* This class creates an OpenGL Uniform Buffer
	*/

	class OpenGLUniformBuffer : public UniformBuffer
	{
	private:
		uint32_t m_OpenGL_ID; //!< Render ID
		static uint32_t s_blockNumber; //!< Global block number

	public:
		OpenGLUniformBuffer(const UniformBufferLayout& layout); //!< Constructor
		~OpenGLUniformBuffer(); //!< Virtual distructor
		inline uint32_t getRenderID() const override { return m_OpenGL_ID; } //!< Get the render ID
		const inline UniformBufferLayout& getLayout() const override { return m_layout; } //!< Get the layout
		void attachShaderBlock(const std::shared_ptr<Shader>& shader, const char* blockName) override; //!< Attach shader block
		void uploadData(const char* uniformName, void* data) override; //!< Upload data to the shader block


	};
}