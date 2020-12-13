/** \ file textureUnitManager.h*/

#pragma once

#include <vector>

namespace Engine
{
	/**\class TextureUnitManager
    ** \brief This class manages textures in an optiman way
    */
	class TextureUnitManager
	{
	private:
		uint32_t m_capacity; //!< Capacity of ring buffer
		std::vector<uint32_t> m_buffer; //!< Internal buffer
		bool m_full = false; //!< Is the buffer full?
		uint32_t m_head = 0; //!< Head of the buffer
		uint32_t m_tail = 0; //!< Tail of the buffer

	public:
		TextureUnitManager(uint32_t capacity) : m_capacity(capacity), m_buffer(capacity, 0xFFFFFFFF) {} //!< Constructor
		inline bool full() { return m_full; } //!< is the buffer full?
		void clear(); //!< Clear the rest of the buffer
		bool getUnit(uint32_t textureID, uint32_t& textureUnit); //!< Returns whether or not the texture needs binding to the unit. Texture unit is always set to the unit

	};
}
