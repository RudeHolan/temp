#include "engine_pch.h"
#include "rendering/bufferLayout.h"

namespace Engine
{
	void BufferLayout::addElement(BufferElement dataType)
	{
		m_elements.push_back(dataType);
		calcStrideAndOffset();
	}

	void BufferLayout::calcStrideAndOffset()
	{
		uint32_t l_offset = 0;
		for (auto& element : m_elements)
		{
			element.m_offset = l_offset;
			l_offset += element.m_size;
		}

		if(m_stride == 0) m_stride = l_offset;
	}
}