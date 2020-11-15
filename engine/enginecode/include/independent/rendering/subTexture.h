/*\ file subTexture.h*/

#pragma once

#include "rendering/texture.h"
#include <memory>
#include <glm/glm.hpp>

namespace Engine
{	/**
	\class SubTexture - This class creates subtextures out of a single texture (think sprite sheets)
	*/
	class SubTexture
	{
	private:
		std::shared_ptr<Texture> m_texture; //!< The texture 
		glm::vec2 m_UVStart;  //!< UV start coordinates
		glm::vec2 m_UVEnd; //!< UV end coordinates
		glm::ivec2 m_size; //!< Size in pixels

	public:
		SubTexture() {};   //!< default constructor
		SubTexture(const std::shared_ptr<Texture>& texture, const glm::vec2& UVStart, const glm::vec2& UVEnd); //!< Constructor
		inline glm::vec2 getUVStart() { return m_UVStart; } //!< Get the UV start
		inline glm::vec2 getUVEnd() { return m_UVEnd; } //!< Get the UV End
		glm::ivec2 getSize() { return m_size; } //!< get the size
		glm::vec2 getSizef() { return { static_cast<float>(m_size.x), static_cast<float>(m_size.y) }; } //!< Get the size(in vec2)
		inline uint32_t getWidth() { return m_size.x; } //!< Get the width
		inline uint32_t getHeight() { return m_size.y; } //!< Get the height 
		inline uint32_t getWidthf() { return static_cast<float>(m_size.x); } //!< Get the width in float
		inline uint32_t getHeightf() { return static_cast<float>(m_size.y); } //!< Get the height in float
		float transformU(float U); //!< Transform original to atlased co-ords (U)
		float transformV(float V);//!< Transform original to atlased co-ords (V)
		glm::vec2 transformUV(glm::vec2 UV); //!< Transform original to atlased co-ords (UV)
	
	
	};


}
