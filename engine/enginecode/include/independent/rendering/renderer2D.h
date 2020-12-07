/*file renderer2D.h*/

#pragma once

#include "rendering/rendererCommon.h"

namespace Engine
{
	class Quad;

	class Renderer2D
	{
	private:
		struct InternalData
		{
			std::shared_ptr<Texture> defaultTexture;
			glm::vec4 defaultTint;
			std::shared_ptr<Shader> shader;
			std::shared_ptr<VertexArray> VAO;
			glm::mat4 model;
		};

		static std::shared_ptr<InternalData> s_data;

	public:
		static void init(); //!< Init the internal data of the renderer
		static void begin(const SceneWideUniforms& swu); //!< Begin a 2D scene
		static void submit(const Quad& quad, glm::vec4& tint); //!< Render a tinted quad
		static void end();

	};
}