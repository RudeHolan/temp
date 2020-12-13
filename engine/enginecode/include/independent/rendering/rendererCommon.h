/** \file rendererCommon.h
* A header file which includes all of the common headers which the 2D and 3D renderers share 
*/

#pragma once

#include <glm/glm.hpp>
#include <unordered_map>
#include <memory>
#include "rendering/vertexArray.h"
#include "rendering/shaderDataType.h"
#include "rendering/shader.h"
#include "rendering/texture.h"
#include "rendering/renderCommands.h"

namespace Engine {

	using SceneWideUniforms = std::unordered_map<const char*, std::pair<ShaderDataType, void*>>;
	
	/**\class RendererCommon
	** \brief A class which allows the renderers to use commmands
	*/
	class RendererCommon
	{
	public:
		static void actionCommand(std::shared_ptr<RenderCommand>& command) { command->m_action(); }
	};
}