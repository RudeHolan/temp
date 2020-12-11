/**\file renderer3D.cpp */

#include "engine_pch.h"
#include "rendering/renderer3D.h"

namespace Engine
{
	std::shared_ptr<Renderer3D::InternalData> Renderer3D::s_data = nullptr;

	void Renderer3D::init()
	{
		s_data.reset(new InternalData);
		unsigned char whitePixel[4] = { 255,255,255,255 };
		s_data->defaultTexture.reset(Texture::create(1, 1, 4, whitePixel));
		s_data->defaultTint = { 1.f,1.f,1.f,1.f };
	}

	void Renderer3D::begin(const SceneWideUniforms& sceneWideUniformz)
	{
		s_data->sceneWideUniforms = sceneWideUniformz;
	}

	void Renderer3D::submit(const std::shared_ptr<VertexArray>& geometry, const std::shared_ptr<Material>& material, const glm::mat4& model)
	{
		//Setting the render commands
		std::shared_ptr<RenderCommand> useProgramCommand, bindVertexArrayCommand, bindBufferCommand, bindTextureCommand, drawTriangles;
		useProgramCommand.reset(RenderCommandFactory::createCommand(RenderCommand::Commands::useProgram, material->getShader()->getID()));
		bindVertexArrayCommand.reset(RenderCommandFactory::createCommand(RenderCommand::Commands::bindVertexArray, geometry->getID()));
		bindBufferCommand.reset(RenderCommandFactory::createCommand(RenderCommand::Commands::bindBuffer, geometry->getIndexBuffer().getID()));
		drawTriangles.reset(RenderCommandFactory::createCommand(RenderCommand::Commands::drawTriangles, geometry->getDrawCount()));
	
		// Bind shader
		RendererCommon::actionCommand(useProgramCommand);

		// Apply sceneWideUniforms
		for (auto& dataPair : s_data->sceneWideUniforms)
		{
			const char* nameOfUniform = dataPair.first;
			ShaderDataType& sdt = dataPair.second.first;
			void* addressOfValue = dataPair.second.second;

			switch (sdt)
			{
			case ShaderDataType::Int:
				material->getShader()->uploadInt(nameOfUniform, *(int*)addressOfValue);
				break;

			case ShaderDataType::Float3:
				material->getShader()->uploadFloat3(nameOfUniform, *(glm::vec3*)addressOfValue);
				break;

			case ShaderDataType::Float4:
				material->getShader()->uploadFloat4(nameOfUniform, *(glm::vec4*)addressOfValue);
				break;

			case ShaderDataType::Mat4:
				material->getShader()->uploadMat4(nameOfUniform, *(glm::mat4*)addressOfValue);
				break;
			}
		}

		// Apply material uniforms (per draw uniforms)
		material->getShader()->uploadMat4("u_model", model);

		if (material->isFlagSet(Material::flag_texture)) bindTextureCommand.reset(RenderCommandFactory::createCommand(RenderCommand::Commands::bind2DTexture, material->getTexture()->getID()));
		else  bindTextureCommand.reset(RenderCommandFactory::createCommand(RenderCommand::Commands::bind2DTexture, s_data->defaultTexture->getID()));
		RendererCommon::actionCommand(bindTextureCommand);

		material->getShader()->uploadInt("u_texData", 0);

		if (material->isFlagSet(Material::flag_tint)) material->getShader()->uploadFloat4("u_tint", material->getTint());
		else  material->getShader()->uploadFloat4("u_tint", s_data->defaultTint);

		// Bind geometry (vao and ibo)
		RendererCommon::actionCommand(bindVertexArrayCommand);
		RendererCommon::actionCommand(bindBufferCommand);
		// Submit the draw call
		RendererCommon::actionCommand(drawTriangles);
	}

	void Renderer3D::end()
	{
		s_data->sceneWideUniforms.clear();
	}

}