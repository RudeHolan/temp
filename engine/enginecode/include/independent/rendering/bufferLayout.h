/*\file bufferLayout.h*/
#pragma once

#include "shaderDataType.h"
#include <vector>
#include <cstdint>

namespace Engine
{

	/**
	\class VertexBufferElement
	** \brief A class which holds data about a single element in a vertex buffer layout
	*/

	class VertexBufferElement
	{
	public:
		ShaderDataType m_dataType; //!< The data type (float, mat, etc)
		uint32_t m_size; //!< the size 
		uint32_t m_offset; //!< the offset 
		bool m_normalised; //!< is it normalised or not

		VertexBufferElement() {} //!< Default constructor
		VertexBufferElement(ShaderDataType dataType, bool normalised = false) :
			m_dataType(dataType),
			m_size(SDT::size(dataType)),
			m_offset(0),
			m_normalised(normalised)
		{} //!< Constructor with parameters

	};

	/**
    \class UniformBufferElement
   ** \brief  A class which holds data about a single element in a uniform buffer layout
    */
	class UniformBufferElement
	{
	public:
		const char* m_name; //!< Name of the uniform buffer element
		ShaderDataType m_dataType; //!< The data type (float, mat, etc)
		uint32_t m_size; //!< the size 
		uint32_t m_offset; //!< the offset 

		UniformBufferElement() {} //!< Default constructor
		UniformBufferElement(const char* name, ShaderDataType dataType) :
			m_name(name),
			m_dataType(dataType),
			m_size(SDT::std140alignment(dataType)),
			m_offset(0)
		{} //!< Constructor with parameters

	};


	/**
    \class BufferLayout
	** \brief  Abstraction of the notion of a buffer layout
    */
	template <class G>
	class BufferLayout
	{
	private:
		std::vector<G> m_elements; //!< Buffer elements
		uint32_t m_stride; //!< Width in bytes of the buffer line
		void calcStrideAndOffset(); //!< Calculate the stride and the offsets based on the elements

	public:
		BufferLayout<G> () {}
		BufferLayout<G> (const std::initializer_list<G>& element, uint32_t stride = 0) : m_elements(element), m_stride(stride) { calcStrideAndOffset(); } //!< Constructor
		inline uint32_t getStride() const { return m_stride; } //!< get the stride (width in bytes of the buffer line)
		void addElement(G dataType); //!< add an element to the buffer layout
		inline typename std::vector<G>::iterator begin() { return m_elements.begin(); } //!< the first element of the vector
		inline typename std::vector<G>::iterator end() { return m_elements.end(); } //!< the last element of the vector
		inline typename std::vector<G>::const_iterator begin() const { return m_elements.begin(); } //!< Get the first element of the buffer element vector
		inline typename std::vector<G>::const_iterator end() const { return m_elements.end(); } //!< Get the last element of the buffer element vector
	};

	template <class G>
	void BufferLayout<G>::addElement(G dataType)
	{
		m_elements.push_back(dataType);
		calcStrideAndOffset();
	}

	template <class G>
	void BufferLayout<G>::calcStrideAndOffset()
	{
		uint32_t l_offset = 0;
		for (auto& element : m_elements)
		{
			element.m_offset = l_offset;
			l_offset += element.m_size;
		}

		if (m_stride == 0) m_stride = l_offset;
	}

	using VertexBufferLayout = BufferLayout<VertexBufferElement>;
	using UniformBufferLayout = BufferLayout<UniformBufferElement>;


}
