/*file renderer3D.h*/
#pragma once

#include <glm/glm.hpp>
#include <unordered_map>
#include <memory>
#include "rendering/vertexArray.h"
#include "rendering/texture.h"
#include "rendering/shader.h"
#include "rendering/shaderDataType.h"
#include "rendering/renderAPI.h"

namespace Engine {

	using SceneWideUniforms = std::unordered_map<const char*, std::pair<ShaderDataType, void*>>;

	class Material;

	/**\class Renderer3D
	** \brief A class which renders 3D geometry instantly (non-batched
	*/
	class Renderer3D
	{
	private:
		struct InternalData
		{
			SceneWideUniforms sceneWideUniforms; //!< Replace with UBO
			std::shared_ptr<Texture> defaultTexture; //!< Empty white texture
			glm::vec4 defaultTinte; //!< Default white tint
		};
	
		static std::shared_ptr<InternalData> s_data; //!< Data internal to the renderer
	
	public:
		static void init(); //!< Initialize the renderer
		static void begin(const SceneWideUniforms& sceneWideUniformz); //!< Begin a new 3D scene
		static void submit(const std::shared_ptr<VertexArray>& geometry, const std::shared_ptr<Material>& material, const glm::mat4& model); //!< Submit a piece of geometry to be rendered
		static void end(); //!< End the 3D scene
	};
}