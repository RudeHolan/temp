#include "UILayer.h"


using namespace Engine;

UILayer::UILayer(const char* name) : Layer(name)
{
	auto& window = Application::getInstance().getWindow();

	m_cam.reset(new CameraController(window->getWidth()/window->getHeight()));

	enableBlend.reset(RenderCommandFactory::createCommand(RenderCommand::Commands::enableBlend));
	disableDepthTest.reset(RenderCommandFactory::createCommand(RenderCommand::Commands::disableDepthTest));
	setBlendFuncDefault.reset(RenderCommandFactory::createCommand(RenderCommand::Commands::setBlendFuncDefault));

	

	//m_swu["u_view"] = std::pair<ShaderDataType, void*>(ShaderDataType::Mat4, static_cast<void*>(glm::value_ptr(m_cam->getCamera().m_view)));
	//m_swu["u_projection"] = std::pair<ShaderDataType, void*>(ShaderDataType::Mat4, static_cast<void*>(glm::value_ptr(m_cam->getCamera().m_projection)));

	m_quads.push_back(Quad::createCentreHalfExtents({ 512.f, 750.f }, { 512.f, 50.f }));


}

void UILayer::onRender()
{
	//RendererCommon::actionCommand(disableDepthTest);
	//RendererCommon::actionCommand(enableBlend);
	//RendererCommon::actionCommand(setBlendFuncDefault);

	Renderer2D::begin(m_swu);

	Renderer2D::submit(m_quads[0], { 0.f, 0.f, 1.f, 1.f });
	Renderer2D::submit("Simple Camera Controller", { 20.f, 750.f }, { 1.f, 1.f, 0.f, 1.f });

	Renderer2D::end();

}
