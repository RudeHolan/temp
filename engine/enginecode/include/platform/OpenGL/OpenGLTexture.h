/*\ file OpenGLTexture.h*/
#pragma once

#include "rendering/texture.h"

namespace Engine
{	
	/**\class OpenGLTexture
	* This class creates an OpenGL texture
	*/
	class OpenGLTexture : public Texture
	{
	private:
		uint32_t m_OpenGL_ID; //!< The render ID
		uint32_t m_width; //!< The width of the texture
		uint32_t m_height; //!< The height of the texture
		uint32_t m_channels; //!< The channels of the texture
		void init(uint32_t width, uint32_t height, uint32_t channels, unsigned char* data); //!< Initializing the texture

	public:
		OpenGLTexture(const char* filepath); //!< Constructor 
		OpenGLTexture(uint32_t width, uint32_t height, uint32_t channels, unsigned char* data); //!< Second constructor 
		~OpenGLTexture();  //!< Destructor
		void edit(uint32_t offsetX, uint32_t offsetY, uint32_t width, uint32_t height, unsigned char* data); //!< Edit the texture
		inline uint32_t getRenderID() { return m_OpenGL_ID; } //!< Get the render ID
		inline uint32_t getWidth() { return m_width; } //!< Get the width in int format
		inline uint32_t getHeight() { return m_height; } //!< Get the height in int format
		inline uint32_t getWidthf() { return static_cast<float>(m_width); } //!< Get the width in int format
		inline uint32_t getHeightf() { return static_cast<float>(m_height); } //!< Get the height in int format
		inline uint32_t getChannels() { return m_channels; } //!< Get the channels
	};
}
