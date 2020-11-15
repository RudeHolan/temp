/*\ file OpenGLVertexArray.h */

#pragma once

#include "rendering/vertexArray.h"


namespace Engine

{    /**\class OpenGLVertexArray
	 * This class creates an OpenGL Vertex Array
	 */

	class OpenGLVertexArray : public VertexArray
	{

	private:

		std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffer; //!< The vertex buffer
		std::shared_ptr<IndexBuffer> m_indexBuffer; //!< The index buffer
		uint32_t m_OpenGL_ID; //!< Render ID
		uint32_t m_attributeIndex = 0; //!< Vertex array attribute index


	public:

		OpenGLVertexArray(); //!< Constructor
		virtual ~OpenGLVertexArray(); //!< virtual destructor
		void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer); //!< Add a vertex buffer
		void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer); //!< Add an index buffer
		inline uint32_t getRenderID() const { return m_OpenGL_ID; } //!< Get the render ID
		inline uint32_t getDrawCount() { if (m_indexBuffer) { return m_indexBuffer->getCount(); } else { return 0; } }; //!< Get the draw count of the ibo

	};
}