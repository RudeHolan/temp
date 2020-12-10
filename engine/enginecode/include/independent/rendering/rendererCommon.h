/**\file rendererCommon.h*/

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

	class RendererCommon
	{
	public:
		static void actionCommand(std::shared_ptr<RenderCommand>& command) { command->m_action(); }
	};
}