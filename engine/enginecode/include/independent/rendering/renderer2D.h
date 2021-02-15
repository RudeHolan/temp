/*file renderer2D.h*/

#pragma once

#include "rendering/rendererCommon.h"
#include "ft2build.h"
#include "freetype/freetype.h"

namespace Engine
{
	/**
	\class Quad
	** \brief this class holds the information for a render command
	*/

	class Renderer2DVertex
	{
	public:
		Renderer2DVertex() = default;
		Renderer2DVertex(const glm::vec4& pos, const glm::vec2& UV, const uint32_t tUnits, const glm::vec4& pTint) : position(pos), uvCoords(UV), texUnits(tUnits), tint(pack(pTint)) {}
		glm::vec4 position;
		glm::vec2 uvCoords;
		uint32_t texUnits;
		uint32_t tint;
		static VertexBufferLayout layout;
		static uint32_t pack(const glm::vec4& tint);
	};

	class Quad
	{
	private:
		glm::vec3 m_translate = glm::vec3(0.f); //!< Translation vector
		glm::vec3 m_scale = glm::vec3(1.f); //!< Scale vector
		friend class Renderer2D; 

	public:
		Quad() = default; //!< default constructor
		static Quad createCentreHalfExtents(const glm::vec2& centre, const glm::vec2& halfExtents); //!< creates a single quad
	};

	/**
    \class Renderer2D
	** \brief This is the 2D renderer 
    */
	class Renderer2D
	{
	private:

		struct InternalData
		{
			std::shared_ptr<Texture> defaultTexture;
			SubTexture defaultSubTexture;
			glm::vec4 defaultTint;
			std::shared_ptr<Shader> shader;
			std::shared_ptr<VertexArray> VAO;
			std::shared_ptr<UniformBuffer> UBO;
			glm::mat4 model;
			std::array<glm::vec4, 4> quads;
			std::array<Renderer2DVertex, 4> vertices;
			std::array<int32_t, 32> textureUnits;

			FT_Library ft;
			FT_Face fontFace;
			std::shared_ptr<Texture> fontTexture;
			glm::ivec2 glyphBufferDimensions;
			uint32_t glyphBufferSize;
			uint32_t glyphBufferChannels;
			std::shared_ptr<unsigned char> glyphBuffer;
		}; //!< A struct that holds all of the information a 2d object can have 

		static std::shared_ptr<InternalData> s_data; //!< the data that a 2D object holds


		static void RtoRGBA(unsigned char* Rbuffer, uint32_t width, uint32_t height); //!< Convert a single R channel to an RGBA

	public:
		static void init(); //!< Init the internal data of the renderer
		static void begin(const SceneWideUniforms& swu); //!< Begin a 2D scene
		static void submit(const Quad& quad, const glm::vec4& tint); //!< Render a tinted quad
		static void submit(const Quad& quad, const SubTexture& texture); //!< Render a textured quad
		static void submit(const Quad& quad, const glm::vec4& tint, const SubTexture& texture); //!< Render a textured and tinted quad

		static void submit(const Quad& quad, const glm::vec4& tint, float angle, bool degrees = false); //!< Render a tinted quad thats rotated
		static void submit(const Quad& quad, const SubTexture& texture, float angle, bool degrees = false); //!< Render a textured quad thats rotated
		static void submit(const Quad& quad, const glm::vec4& tint, const SubTexture& texture, float angle, bool degrees = false); //!< Render a textured and tinted quad thats rotated 

		static void submit(char character, const glm::vec2& position, float& advance, const glm::vec4& tint); //!< Render a single character with a tint
		static void submit(const char* text, const glm::vec2& position, const glm::vec4& tint); //!< Render a single character with a tint

		static void end(); //!< End a 2D scene

	};
}