#pragma once

#include "engine.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <rendering/renderer2D.h>



using namespace Engine;

class SceneLayer : public Layer
{
public:
	SceneLayer(const char* name);
	void onRender() override;
private:
	std::shared_ptr<CameraController> m_cam;
	std::shared_ptr<RenderCommand> enableBlend, disableDepthTest, setBlendFuncDefault;
	SceneWideUniforms m_swu;
	std::vector<Quad> m_quads;
};


