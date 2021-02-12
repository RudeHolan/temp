#pragma once

#include "engine.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <rendering/renderer2D.h>


using namespace Engine;

	class UILayer : public Layer
	{
	public:
		UILayer(const char* name);
		void onRender() override;
	private:
		std::shared_ptr<CameraController> m_cam;
		SceneWideUniforms m_swu;
		std::shared_ptr<RenderCommand> enableBlend, disableDepthTest, setBlendFuncDefault;
		std::vector<Quad> m_quads;
		

	};



