/*\file vertexArray.h*/

#pragma once

#include <cstdint>
#include <memory>
#include "rendering/vertexBuffer.h"
#include "rendering/indexBuffer.h"

namespace Engine {
	
    /**\class VertexArray
    ** \brief API agnostic vertex array
    */

    class VertexArray
    {
    public:
        virtual ~VertexArray() = default; //!< Virtual distructor
        virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0; //!< Add a vertex buffer 
        virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0; //!< Add an index buffer
        virtual IndexBuffer& getIndexBuffer() const = 0; //!< Get the index buffer
        virtual std::vector<std::shared_ptr<VertexBuffer>> getVertexBuffers() const = 0; //!< Get the vertex buffer
        virtual inline uint32_t getID() const = 0; //!< Get the render ID
        virtual inline uint32_t getDrawCount() const = 0; //!< Get the draw count

        static VertexArray* create(); //!< Create a vertex array

    };


}