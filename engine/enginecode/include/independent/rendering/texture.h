/*\ file texture.h*/
#pragma once

#include <cstdint>

namespace Engine
{
	/**\class Texture
	* API agnostic texture
	*/
	class Texture
	{

	public:
		
		virtual ~Texture() = default; //!< Virtual destructor
		virtual void edit(uint32_t offsetX, uint32_t offsetY, uint32_t width, uint32_t height, unsigned char* data) = 0; //!< Edit the texture
		virtual inline uint32_t getRenderID() = 0; //!< Get the render ID
		virtual inline uint32_t getWidth() = 0; //!< Get the width in int format
		virtual inline uint32_t getHeight() = 0; //!< Get the height in int format
		virtual inline uint32_t getWidthf() = 0; //!< Get the width in float format
		virtual inline uint32_t getHeightf() = 0; //!< Get the height in float format
		virtual inline uint32_t getChannels() = 0; //!< Get the channels in int format

		static Texture* create(const char* filepath); //!< Create a texture
		static Texture* create(uint32_t width, uint32_t height, uint32_t channels, unsigned char* data); //!< Create a texture (using different arguments)

	};
}
