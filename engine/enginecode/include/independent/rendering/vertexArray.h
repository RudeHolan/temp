/*\file vertexArray.h*/

#pragma once

#include <cstdint>
#include <memory>
#include "rendering/vertexBuffer.h"
#include "rendering/indexBuffer.h"

namespace Engine {
	
    /**\class VertexArray
    * API agnostic vertex buffer
    */

    class VertexArray
    {
    public:
        virtual ~VertexArray() = default; //!< Destroy the vertex array
        virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0; //!< Add a vertex buffer 
        virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0; //!< Add an index buffer
        virtual inline uint32_t getRenderID() const = 0; //!< Get the render ID
        virtual inline uint32_t getDrawCount() = 0; //!< Get the draw count

        static VertexArray* create(); //!< Create a vertex array

    };


}