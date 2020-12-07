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
		s_data->defaultTinte = { 1.f,1.f,1.f,1.f };
	}

	void Renderer3D::begin(const SceneWideUniforms& sceneWideUniformz)
	{
		s_data->sceneWideUniforms = sceneWideUniformz;
	}

	void Renderer3D::submit(const std::shared_ptr<VertexArray>& geometry, const std::shared_ptr<Material>& material, const glm::mat4& model)
	{

	}

	void Renderer3D::end()
	{
		s_data->sceneWideUniforms.clear();
	}

}