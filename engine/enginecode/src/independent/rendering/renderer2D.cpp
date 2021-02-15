/* \file renderer2D.cpp*/
#include "engine_pch.h"
#include "systems/log.h"
#include <glad/glad.h>
#include "rendering/renderer2D.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Engine {
	
	
	VertexBufferLayout Renderer2DVertex::layout = VertexBufferLayout({ ShaderDataType::Float4, ShaderDataType::Float2, ShaderDataType::FlatInt, {ShaderDataType::Byte4, true} });

	std::shared_ptr<Renderer2D::InternalData> Renderer2D::s_data = nullptr;


	void Renderer2D::init()
	{
		s_data.reset(new InternalData);
		
		unsigned char whitePixel[4] = { 255, 255, 255, 255 };
		s_data->defaultTexture.reset(Texture::create(1, 1, 4, whitePixel));
		s_data->defaultSubTexture = SubTexture(s_data->defaultTexture, { 0.f,0.f }, { 0.f , 0.f });

		s_data->defaultTint = { 1.f, 1.f, 1.f, 1.f };

		s_data->model = glm::mat4(1.0f);

		s_data->textureUnits = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };

 		s_data->shader.reset(Shader::create("./assets/shaders/quad1.glsl"));

		s_data->UBO.reset(UniformBuffer::create(UniformBufferLayout({
			{ "u_projection", ShaderDataType::Mat4 },
			{ "u_view", ShaderDataType::Mat4 }
			})));


		s_data->quads[0] = { -0.5f, -0.5f, 1.f, 1.f };
		s_data->quads[1] = { -0.5f,  0.5f, 1.f, 1.f };
		s_data->quads[2] = { 0.5f,  0.5f, 1.f, 1.f };
		s_data->quads[3] = { 0.5f, -0.5f, 1.f, 1.f };

		s_data->vertices[0] = Renderer2DVertex(s_data->quads[0], { 0.f, 0.f }, 0, glm::vec4(1.f));
		s_data->vertices[1] = Renderer2DVertex(s_data->quads[1], { 0.f, 0.f }, 0, glm::vec4(1.f));
		s_data->vertices[2] = Renderer2DVertex(s_data->quads[2], { 0.f, 0.f }, 0, glm::vec4(1.f));
		s_data->vertices[3] = Renderer2DVertex(s_data->quads[3], { 0.f, 0.f }, 0, glm::vec4(1.f));
		uint32_t indices[4] = { 0,1,2,3 };

		std::shared_ptr<VertexBuffer> VBO;
		std::shared_ptr<IndexBuffer> IBO;

		s_data->VAO.reset(VertexArray::create());
		VBO.reset(VertexBuffer::create(s_data->vertices.data(), sizeof(Renderer2DVertex) * s_data->vertices.size(), Renderer2DVertex::layout));
		IBO.reset(IndexBuffer::create(indices, 4));
		s_data->VAO->addVertexBuffer(VBO);
		s_data->VAO->setIndexBuffer(IBO);

		s_data->UBO->attachShaderBlock(s_data->shader, "b_camera");

		//File path to a font
		const char* filePath = "./assets/fonts/arial.ttf";

		//Set the dimensions of the glyph buffer
		s_data->glyphBufferDimensions = { 256, 256 };
		s_data->glyphBufferChannels = 4;
		s_data->glyphBufferSize = s_data->glyphBufferDimensions.x * s_data->glyphBufferDimensions.y * s_data->glyphBufferChannels * sizeof(unsigned char);
		s_data->glyphBuffer.reset(static_cast<unsigned char *>(malloc(s_data->glyphBufferSize)));

		//Init Freetype lib
		if (FT_Init_FreeType(&s_data->ft)) Log::error("Error: Freetype could not be initialised");

		// Load the font
		if (FT_New_Face(s_data->ft, filePath, 0, &s_data->fontFace)) Log::error("Error: Freetype could not load font: {0}", filePath);

		//Set the char size
		int32_t charSize = 86;
		if (FT_Set_Pixel_Sizes(s_data->fontFace, 0, charSize)) Log::error("Error: Freetype can't set font size: {0}", charSize);
	
		// Init font text
		s_data->fontTexture.reset(Texture::create(s_data->glyphBufferDimensions.x , s_data->glyphBufferDimensions.y, s_data->glyphBufferChannels, nullptr));

		// Fill the glyph buffer 
		memset(s_data->glyphBuffer.get(), 60, s_data->glyphBufferSize);

		// Send glyph buffer to the texture on the gpu
		s_data->fontTexture->edit(0, 0, s_data->glyphBufferDimensions.x, s_data->glyphBufferDimensions.y, s_data->glyphBuffer.get());


	}

	void Renderer2D::begin(const SceneWideUniforms& swu)
	{
#pragma region RenderCommands
		
			std::shared_ptr<RenderCommand> useProgramCommand;
			useProgramCommand.reset(RenderCommandFactory::createCommand(RenderCommand::Commands::useProgram, s_data->shader->getID()));
			
#pragma endregion

		//Bind the shader
		RendererCommon::actionCommand(useProgramCommand);
		glUseProgram(s_data->shader->getID());

		// Apply sceneWideUniforms
		s_data->shader->uploadIntArray("u_texData", s_data->textureUnits.data(), 32);
		glBindBuffer(GL_UNIFORM_BUFFER, s_data->UBO->getID());
		s_data->UBO->uploadData("u_projection", swu.at("u_projection").second);
		s_data->UBO->uploadData("u_view", swu.at("u_view").second);
	


		//Bind the geometry (vao and ibo)
		glBindVertexArray(s_data->VAO->getID());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_data->VAO->getIndexBuffer().getID());
	}

	void Renderer2D::submit(const Quad& quad, const glm::vec4& tint)
	{
		Renderer2D::submit(quad, tint, s_data->defaultSubTexture);
	}

	void Renderer2D::submit(const Quad& quad, const SubTexture& texture)
	{
		Renderer2D::submit(quad, s_data->defaultTint, texture);
	}

	void Renderer2D::submit(const Quad& quad, const glm::vec4& tint, const SubTexture& texture)
	{
		glBindTexture(GL_TEXTURE_2D, texture.getBaseTexture()->getID());
		s_data->model = glm::scale(glm::translate(glm::mat4(1.f), quad.m_translate), quad.m_scale);
		uint32_t packedTint = Renderer2DVertex::pack(tint);
	    
		for (int i = 0; i < 4; i++ )
		{
			s_data->vertices[i].position = s_data->model * s_data->quads[i];
			s_data->vertices[i].tint = packedTint;
		}

		//Should this be here as well??
		s_data->vertices[0].uvCoords = texture.getUVStart();
		s_data->vertices[1].uvCoords = { texture.getUVStart().x, texture.getUVEnd().y };
		s_data->vertices[2].uvCoords = texture.getUVEnd();
		s_data->vertices[3].uvCoords = { texture.getUVEnd().x, texture.getUVStart().y };

		s_data->VAO->getVertexBuffers().at(0)->edit(s_data->vertices.data(), sizeof(Renderer2DVertex) * s_data->vertices.size(), 0);

		glDrawElements(GL_QUADS, s_data->VAO->getDrawCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer2D::submit(const Quad& quad, const glm::vec4& tint, float angle, bool degrees)
	{
		Renderer2D::submit(quad, tint, s_data->defaultSubTexture, angle, degrees);
	}

	void Renderer2D::submit(const Quad& quad, const SubTexture& texture, float angle, bool degrees)
	{
		Renderer2D::submit(quad, s_data->defaultTint, texture, angle, degrees);
	}

	void Renderer2D::submit(const Quad& quad, const glm::vec4& tint, const SubTexture& texture, float angle, bool degrees)
	{
		if (degrees) angle - glm::radians(angle);

		glBindTexture(GL_TEXTURE_2D, texture.getBaseTexture()->getID());
		s_data->model = glm::scale(glm::rotate(glm::translate(glm::mat4(1.f), quad.m_translate), angle, { 0.f, 0.f, 1.f }), quad.m_scale);

		uint32_t packedTint = Renderer2DVertex::pack(tint);

		for (int i = 0; i < 4; i++)
		{
			s_data->vertices[i].position = s_data->model * s_data->quads[i];
			s_data->vertices[i].tint = packedTint;
		}

		s_data->vertices[0].uvCoords = texture.getUVStart();
		s_data->vertices[1].uvCoords = { texture.getUVStart().x, texture.getUVEnd().y };
		s_data->vertices[2].uvCoords = texture.getUVEnd();
		s_data->vertices[3].uvCoords = { texture.getUVEnd().x, texture.getUVStart().y };

		s_data->VAO->getVertexBuffers().at(0)->edit(s_data->vertices.data(), sizeof(Renderer2DVertex) * s_data->vertices.size(), 0);

		glDrawElements(GL_QUADS, s_data->VAO->getDrawCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer2D::RtoRGBA(unsigned char* Rbuffer, uint32_t width, uint32_t height)
	{

		memset(s_data->glyphBuffer.get(), 0, s_data->glyphBufferSize);

		unsigned char * pWalker = s_data->glyphBuffer.get();
		for (int32_t i = 0; i < height; i++)
		{
			for (int32_t j = 0; j < width; j++)
			{
				*pWalker = 255; pWalker++; // Go to G
				*pWalker = 255; pWalker++; // Go to B
				*pWalker = 255; pWalker++; // Go to A
				*pWalker = *Rbuffer; // Set alpha channel
				pWalker++; // Go to R of the next pixel
				Rbuffer++; // Go next monochrome pixel
			}
			pWalker += (s_data->glyphBufferDimensions.x - width) * 4;
		}
	}

	void Renderer2D::submit(char character, const glm::vec2& position, float& advance, const glm::vec4& tint)
	{
		// Get glyph from freetype
		if (FT_Load_Char(s_data->fontFace, character, FT_LOAD_RENDER)) Log::error("Error: Could no load  glyph or char {0}", character);
		else
		{
			// Get glyph data
			uint32_t glyphWidth = s_data->fontFace->glyph->bitmap.width;
			uint32_t glyphHeight = s_data->fontFace->glyph->bitmap.rows;
			glm::vec2 glyphSize(glyphWidth, glyphHeight);
			glm::vec2 glyphBearing(s_data->fontFace->glyph->bitmap_left, -s_data->fontFace->glyph->bitmap_top);
		    
			// Calculate the advance
			advance = static_cast<float>(s_data->fontFace->glyph->advance.x >> 6);

			// Calculate the quad for the glyph
			glm::vec2 glyphHalfExtents = glm::vec2(s_data->fontTexture->getWidthf() * 0.5f, s_data->fontTexture->getHeightf() * 0.5f);
			glm::vec2 glyphCentre = (position + glyphBearing) + glyphHalfExtents;
			Quad quad = Quad::createCentreHalfExtents(glyphCentre, glyphHalfExtents);

			//R to RGBA
			RtoRGBA(s_data->fontFace->glyph->bitmap.buffer, glyphWidth, glyphHeight);
			s_data->fontTexture->edit(0, 0, s_data->glyphBufferDimensions.x, s_data->glyphBufferDimensions.y, s_data->glyphBuffer.get());

			// Submit quad
			SubTexture tmp(s_data->fontTexture, glm::vec2(0.f), glm::vec2(1.f));
			submit(quad, tint, tmp);

		
		}

	
	
	}

	void Renderer2D::submit(const char* text, const glm::vec2& position, const glm::vec4& tint)
	{
		uint32_t lenght = strlen(text);
		float advance = 0.f, x = position.x;


		for (int32_t i = 0; i < lenght; i++)
		{
			submit(text[i], { x, position.y }, advance, tint);
			x += advance;
		}
	}

	void Renderer2D::end()
	{
	}



	Quad Quad::createCentreHalfExtents(const glm::vec2& centre, const glm::vec2& halfExtents)
	{
		Quad result;

		result.m_translate = glm::vec3(centre, 0.f);
		result.m_scale = glm::vec3(halfExtents * 2.f, 1.f);

		return result;
	}

	uint32_t Renderer2DVertex::pack(const glm::vec4& tint)
	{
		uint32_t result = 0;
		uint32_t r = (static_cast<uint32_t>(tint.r * 255.f)) << 0;  // 000R
		uint32_t g = (static_cast<uint32_t>(tint.g * 255.f)) << 8;  // 00G0
		uint32_t b = (static_cast<uint32_t>(tint.b * 255.f)) << 16; // 0B00
		uint32_t a = (static_cast<uint32_t>(tint.a * 255.f)) << 24; // A000
		result = (r | g | b | a);
		return result;
	}

}

