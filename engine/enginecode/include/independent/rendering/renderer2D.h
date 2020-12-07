/*file renderer2D.h*/

#pragma once

#include "rendering/rendererCommon.h"

namespace Engine
{
	class Quad
	{
	private:
		glm::vec3 m_translate = glm::vec3(0.f); //!< Translation vector
		glm::vec3 m_scale = glm::vec3(1.f); //!< Scale vector
		friend class Renderer2D; 

	public:
		Quad() = default;
		static Quad createCentreHalfExtents(const glm::vec2& centre, const glm::vec2& halfExtents);
	};

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