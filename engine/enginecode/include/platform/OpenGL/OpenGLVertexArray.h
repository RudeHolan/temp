/*\ file OpenGLVertexArray.h */

#pragma once

#include "rendering/vertexArray.h"


namespace Engine

{    /**\class OpenGLVertexArray
	 ** \brief This class creates an OpenGL Vertex Array
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
		void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override; //!< Add a vertex buffer
		void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override; //!< Add an index buffer
		IndexBuffer& getIndexBuffer() const override { return *m_indexBuffer; }
		std::vector<std::shared_ptr<VertexBuffer>> getVertexBuffers() const override { return m_vertexBuffer; } 
		inline uint32_t getID() const override { return m_OpenGL_ID; } //!< Get the render ID
		inline uint32_t getDrawCount() const override { if (m_indexBuffer) { return m_indexBuffer->getCount(); } else { return 0; } }; //!< Get the draw count of the ibo

	};
}