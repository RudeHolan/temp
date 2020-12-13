/*\file indexBuffer.h*/

#pragma once

#include <cstdint>

namespace Engine {

	/**\class IndexBuffer 
	** \brief API agnostic index buffer
	*/
	class IndexBuffer {
	public:
		virtual ~IndexBuffer() = default; //!< Virtual destructor
		virtual inline uint32_t getID() const = 0; //!< Get the render ID
		virtual inline uint32_t getCount() const = 0; //!< Get the effective draw count

		static IndexBuffer* create(uint32_t* indices, uint32_t count); //!< Create an index buffer

	};

}