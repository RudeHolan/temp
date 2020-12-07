/*\file uniformBuffer.h*/

#pragma once

#include <cstdint>
#include <memory>
#include <unordered_map>

#include "rendering/bufferLayout.h"
#include "rendering/shader.h"


namespace Engine
{	
	
	/**\class UniformBuffer
	* API agnostic uniform buffer
	*/

	class UniformBuffer
	{
	protected:
		UniformBufferLayout m_layout; //!< The buffer layout
		std::unordered_map<const char*, std::pair<uint32_t, uint32_t>> m_uniformCache; //!< Stores uniform names with offsets and sizes
		uint32_t m_blockNumber; //!< Block number for this UBO

	public:
		virtual ~UniformBuffer() = default; //!< Virtual distructor
		virtual inline uint32_t getRenderID() const = 0; //!< Get the render ID
		virtual const inline UniformBufferLayout& getLayout() const = 0; //!< Get the layout
		virtual void attachShaderBlock(const std::shared_ptr<Shader>& shader, const char* blockName) = 0; //!< Attach shader block
		virtual void uploadData(const char* uniformName, void* data) = 0; //!< Upload data to the shader block

		static UniformBuffer* create(const UniformBufferLayout& layout); //!< Create an index buffer

	};
}