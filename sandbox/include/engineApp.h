#pragma once

// entry point
#include "include/independent/core/entrypoint.h"
#include "engine.h"
#include "UILayer.h"
#include "sceneLayer.h"

class engineApp : public Engine::Application
{
private:
	std::shared_ptr<UILayer> m_uiLayer;
	//std::shared_ptr<SceneLayer> m_sceneLayer;

public:
	engineApp();
	~engineApp() override;

};
