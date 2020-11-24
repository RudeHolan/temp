/*\file bufferLayout.h*/
#pragma once

#include "shaderDataType.h"
#include <vector>
#include <cstdint>

namespace Engine
{

	/**
	\class BufferElement
	A class which holds data about a single element in a buffer layout
	*/

	class BufferElement
	{
	public:
		ShaderDataType m_dataType; //!< The data type (float, mat, etc)
		uint32_t m_size; //!< the size 
		uint32_t m_offset; //!< the offset 
		bool m_normalised; //!< is it normalised or not

		BufferElement() {} //!< Default constructor
		BufferElement(ShaderDataType dataType, bool normalised = false) :
			m_dataType(dataType),
			m_size(SDT::size(dataType)),
			m_offset(0),
			m_normalised(normalised)
		{} //!< Constructor with parameters

	};


	/**
    \class BufferLayout
	Abstraction of the notion of a buffer layout
    */
	class BufferLayout
	{
	private:
		std::vector<BufferElement> m_elements; //!< Buffer elements
		uint32_t m_stride; //!< Width in bytes of the buffer line
		void calcStrideAndOffset(); //!< Calculate the stride and the offsets based on the elements

	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElement>& element, uint32_t stride = 0) : m_elements(element), m_stride(stride) { calcStrideAndOffset(); }
		inline uint32_t getStride() const { return m_stride; } //!< get the stride (width in bytes of the buffer line)
		void addElement(BufferElement dataType); //!< add an element to the buffer layout
		inline std::vector<BufferElement>::iterator begin() { return m_elements.begin(); } //!< the first element of the vector
		inline std::vector<BufferElement>::iterator end() { return m_elements.end(); } //!< the last element of the vector
		inline std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); } //!< Get the first element of the buffer element vector
		inline std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); } //!< Get the last element of the buffer element vector
	};



}
