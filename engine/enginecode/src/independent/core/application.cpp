/** \file application.cpp
*/

#include "engine_pch.h"
#include <glad/glad.h>
#include "core/application.h"

#ifdef NG_PLATFORM_WINDOWS
#include "platform/GLFW/GLFWSystem.h"
#endif


#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "rendering/indexBuffer.h"#
#include "rendering/vertexBuffer.h"
#include "rendering/vertexArray.h"
#include "rendering/subTexture.h"
#include "rendering/shader.h"
#include "rendering/texture.h"
#include "rendering/uniformBuffer.h"

namespace Engine {


	
#pragma region TEMP_CLASS
	class FCVertex
	{
	private:
		static VertexBufferLayout s_layout;
	public:
		glm::vec3 m_pos;
		uint32_t m_colour;
		FCVertex() : m_pos(glm::vec3(0.f)), m_colour(0.f) {}
		FCVertex(const glm::vec3 pos, const uint32_t& colour) : m_pos(pos), m_colour(colour) {}
		static VertexBufferLayout getLayout() { return s_layout; }
	};

	class TPVertexNormalised
	{
	private:
		static VertexBufferLayout s_layout;
	public:
		glm::vec3 m_pos;
		std::array<int16_t, 3> m_normal;
		std::array<int16_t, 2> m_uv;

		TPVertexNormalised() : m_pos(glm::vec3(0.f)), m_normal({ 0,0,0 }), m_uv({ 0, 0 }) {}
		TPVertexNormalised(const glm::vec3& pos, const std::array<int16_t, 3>& normal, const std::array<int16_t, 2>&uv) :
			m_pos(pos),
			m_normal(normal),
			m_uv(uv) 
		{}
		static VertexBufferLayout getLayout() { return s_layout; }

	};
	
	VertexBufferLayout FCVertex::s_layout = { ShaderDataType::Float3, {ShaderDataType::Byte4, true} };
	VertexBufferLayout TPVertexNormalised::s_layout = { {ShaderDataType::Float3, {ShaderDataType::Short3, true}, {ShaderDataType::Short2, true} }, 24 };

#pragma endregion

	// Set static vars
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		if (s_instance == nullptr)
		{
			s_instance = this;
		}


		// Start logging system
		m_logSystem.reset(new Log);
		m_logSystem->start();


		// Start windows System
#ifdef NG_PLATFORM_WINDOWS
		m_windowsSystem.reset(new GLFWSystem);
#endif
		m_windowsSystem->start();


		// Start timer (not a system)
		m_timer.reset(new ChronoTimer);
		m_timer->start();


		// Create a window
		WindowProperties props("My Game Engine", 1024, 800, false);
		m_window.reset(Window::create(props));


		m_window->getEventHandler().setOnWindowCloseCallback(std::bind(&Application::onClose, this, std::placeholders::_1));
		m_window->getEventHandler().setOnWindowResizeCallback(std::bind(&Application::onResize, this, std::placeholders::_1));
		m_window->getEventHandler().setOnWindowMoveCallback(std::bind(&Application::onWindowMove, this, std::placeholders::_1));
		m_window->getEventHandler().setOnWindowFocusCallback(std::bind(&Application::onFocus, this, std::placeholders::_1));
		m_window->getEventHandler().setOnWindowLostFocusCallback(std::bind(&Application::onLostFocus, this, std::placeholders::_1));

		m_window->getEventHandler().setOnKeyPressCallback(std::bind(&Application::onKeyPress, this, std::placeholders::_1));
		m_window->getEventHandler().setOnKeyReleaseCallback(std::bind(&Application::onKeyRelease, this, std::placeholders::_1));
		//m_window->getEventHandler().setOnKeyTypeCallback(std::bind(&Application::onKeyType, this, std::placeholders::_1));

		m_window->getEventHandler().setOnMouseButtonPressCallback(std::bind(&Application::onButtonPress, this, std::placeholders::_1));
		m_window->getEventHandler().setOnMouseButtonReleaseCallback(std::bind(&Application::onButtonRelease, this, std::placeholders::_1));
		m_window->getEventHandler().setOnMouseScrollCallback(std::bind(&Application::onScroll, this, std::placeholders::_1));
		m_window->getEventHandler().setOnMouseMoveCallback(std::bind(&Application::onMouseMove, this, std::placeholders::_1));

		InputPoller::setNativeWindow(m_window->getNativeWindow());

		m_timer->reset();
	}



	bool Application::onClose(WindowCloseEvent& e)
	{
		e.handle(true);
		m_running = false;
		return e.isHandled();
	}


	bool Application::onResize(WindowResizeEvent& e)
	{
		e.handle(true);
		auto& size = e.getSize();
		//Log::info("Window resizeed info - size X: {0}; size Y: {1}", size.x, size.y);
		return e.isHandled();
	}

	bool Application::onWindowMove(WindowMoveEvent& e)
	{
		e.handle(true);
		auto& pos = e.getPos();
		//Log::info("Window moved (new position) info - new pos X: {0}; new pos Y: {1}", pos.x, pos.y);
		return e.isHandled();
	}

	bool Application::onFocus(WindowFocusEvent& e)
	{
		e.handle(true);
		auto focus = e.getFocus();
		//Log::info("Window focused: {0} (should be 1)", focus);
		return e.isHandled();
	}

	bool Application::onLostFocus(WindowLostFocusEvent& e)
	{
		e.handle(true);
		auto focus = e.getFocus();
		//Log::info("Window lost focus: {0} (should be 0)", focus);
		return e.isHandled();
	}


	bool Application::onKeyPress(KeyPressEvent& e)
	{
		e.handle(true);
		auto keyCode = e.getKeyCode();
		auto repeatCount = e.getRepeatCount();
		//Log::info("Key pressed info - Key code: {0}; Repeat count: {1}", keyCode, repeatCount);
		return e.isHandled();
	}


	bool Application::onKeyRelease(KeyReleaseEvent& e)
	{
		e.handle(true);
		auto keyCode = e.getKeyCode();
		if (keyCode == 96) {
			system("cls");
			//Log::info("Key released info - Key code: {0} (console is cleared)", keyCode);
		}
		else
		{
			//Log::info("Key released info - Key code: {0}", keyCode);
		}
		return e.isHandled();
	}

	/*bool Application::onKeyType(KeyTypeEvent& e)
	{
		e.handle(true);
		auto codePoint = e.getKeyCode();
		Log::info("Key typed info - Code point: {0}", codePoint);
		return e.isHandled();
	}*/

	bool Application::onButtonPress(MouseButtonPressEvent& e)
	{
		e.handle(true);
		auto button = e.getButton();
		//Log::info("Mouse button pressed info - Key code: {0}", button);
		return e.isHandled();
	}

	bool Application::onButtonRelease(MouseButtonReleaseEvent& e)
	{
		e.handle(true);
		auto button = e.getButton();
		//Log::info("Mouse button released info - Key code: {0}", button);
		return e.isHandled();
	}

	bool Application::onScroll(MouseScrollEvent& e)
	{
		e.handle(true);
		auto offX = e.getOffsetX();
		auto offY = e.getOffsetY();
		//Log::info("Mouse Scroll info - X offset: {0}; Y offset: {1}", offX, offY);
		return e.isHandled();
	}

	bool Application::onMouseMove(MouseMoveEvent& e)
	{
		e.handle(true);
		auto posX = e.getX();
		auto posY = e.getY();
		//Log::info("Mouse position info - X possition: {0}; Y possition:{1}", posX, posY); 
		return e.isHandled();
	}


	Application::~Application()
	{

		// Stop logging system
		m_logSystem->stop();

		// Stop window system
		m_windowsSystem->stop();
	}


	std::array<int16_t, 3> normalise(const glm::vec3& normal)
	{
		std::array<int16_t, 3> result;
		if (normal.x == 1.0f) result.at(0) = INT16_MAX;
		else if (normal.x == -1.0f) result.at(0) = INT16_MIN;
		else result.at(0) = static_cast<int16_t>(normal.x * static_cast<float>(INT16_MAX));

		if (normal.y == 1.0f) result.at(1) = INT16_MAX;
		else if (normal.y == -1.0f) result.at(1) = INT16_MIN;
		else result.at(1) = static_cast<int16_t>(normal.y * static_cast<float>(INT16_MAX));

		if (normal.z == 1.0f) result.at(2) = INT16_MAX;
		else if (normal.z == -1.0f) result.at(2) = INT16_MIN;
		else result.at(2) = static_cast<int16_t>(normal.z * static_cast<float>(INT16_MAX));

		return result;
	}

	std::array<int16_t, 2> normalise(const glm::vec2& uv)
	{
		std::array<int16_t, 2> result;
		if (uv.x == 1.0f) result.at(0) = INT16_MAX;
		else if (uv.x == -1.0f) result.at(0) = INT16_MIN;
		else result.at(0) = static_cast<int16_t>(uv.x * static_cast<float>(INT16_MAX));

		if (uv.y == 1.0f) result.at(1) = INT16_MAX;
		else if (uv.y == -1.0f) result.at(1) = INT16_MIN;
		else result.at(1) = static_cast<int16_t>(uv.y * static_cast<float>(INT16_MAX));

		return result;
	}

	uint32_t pack(const glm::vec4& colour)
	{
		uint32_t result = 0;
		uint32_t r = (static_cast<uint32_t>(colour.r * 255.f)) << 0;  // 000R
		uint32_t g = (static_cast<uint32_t>(colour.g * 255.f)) << 8;  // 00G0
		uint32_t b = (static_cast<uint32_t>(colour.b * 255.f)) << 16; // 0B00
		uint32_t a = (static_cast<uint32_t>(colour.a * 255.f)) << 24; // A000
		result = (r | g | b | a);
		return result;
	}

	uint32_t pack(const glm::vec3& colour)
	{
		return pack({ colour.x, colour.y, colour.z, 1.0 });
	}

	void Application::run()
	{

#pragma region TEXTURES

		std::shared_ptr<Texture> letterTexture, numberTexture, letterAndNumbertexture;
		letterTexture.reset(Texture::create("assets/textures/letterCube.png"));
		numberTexture.reset(Texture::create("assets/textures/numberCube.png"));
		letterAndNumbertexture.reset(Texture::create("assets/textures/letterAndNumberCube.png"));

		
		SubTexture letterCube(letterAndNumbertexture, { 0.f,0.f }, { 1.0f,0.5f });
		SubTexture numberCube(letterAndNumbertexture, { 0.f,0.5f }, { 1.0f,1.0f });
		

#pragma endregion




#pragma region RAW_DATA

	
		// This is raw data using subtextures (uncomment the subtextures created in the TEXTURES region) 
		//
		
		std::vector<TPVertexNormalised> cubeVertices(24);
		cubeVertices.at(0) =  TPVertexNormalised({ 0.5f,  0.5f, -0.5f}, normalise({0.f,  0.f, -1.f,}), normalise({letterCube.transformU(0.f),  letterCube.transformV(0.f),}));
		cubeVertices.at(1) =  TPVertexNormalised({ 0.5f, -0.5f, -0.5f}, normalise({0.f,  0.f, -1.f,}), normalise({letterCube.transformU(0.f),  letterCube.transformV(0.5f),}));
		cubeVertices.at(2) =  TPVertexNormalised({-0.5f, -0.5f, -0.5f}, normalise({0.f,  0.f, -1.f,}), normalise({letterCube.transformU(0.33f),letterCube.transformV(0.5f),}));
		cubeVertices.at(3) =  TPVertexNormalised({-0.5f,  0.5f, -0.5f}, normalise({0.f,  0.f, -1.f,}), normalise({letterCube.transformU(0.33f),letterCube.transformV(0.f),}));
		cubeVertices.at(4) =  TPVertexNormalised({-0.5f, -0.5f,  0.5f}, normalise({0.f,  0.f,  1.f,}), normalise({letterCube.transformU(0.33f),letterCube.transformV(0.5f),}));
		cubeVertices.at(5) =  TPVertexNormalised({ 0.5f, -0.5f,  0.5f}, normalise({0.f,  0.f,  1.f,}), normalise({letterCube.transformU(0.66f),letterCube.transformV(0.5f),}));
		cubeVertices.at(6) =  TPVertexNormalised({ 0.5f,  0.5f,  0.5f}, normalise({0.f,  0.f,  1.f,}), normalise({letterCube.transformU(0.66f),letterCube.transformV(0.f),}));
		cubeVertices.at(7) =  TPVertexNormalised({-0.5f,  0.5f,  0.5f}, normalise({0.f,  0.f,  1.f,}), normalise({letterCube.transformU(0.33), letterCube.transformV(0.f),}));
		cubeVertices.at(8) =  TPVertexNormalised({-0.5f, -0.5f, -0.5f}, normalise({0.f, -1.f,  0.f,}), normalise({letterCube.transformU(1.f),  letterCube.transformV(0.f),}));
		cubeVertices.at(9) =  TPVertexNormalised({ 0.5f, -0.5f, -0.5f}, normalise({0.f, -1.f,  0.f,}), normalise({letterCube.transformU(0.66f),letterCube.transformV(0.f),}));
		cubeVertices.at(10) = TPVertexNormalised({ 0.5f, -0.5f,  0.5f}, normalise({0.f, -1.f,  0.f,}), normalise({letterCube.transformU(0.66f),letterCube.transformV(0.5f),}));
		cubeVertices.at(11) = TPVertexNormalised({-0.5f, -0.5f,  0.5f}, normalise({0.f, -1.f,  0.f,}), normalise({letterCube.transformU(1.0f), letterCube.transformV(0.5f),}));
		cubeVertices.at(12) = TPVertexNormalised({ 0.5f,  0.5f,  0.5f}, normalise({0.f,  1.f,  0.f,}), normalise({letterCube.transformU(0.f),  letterCube.transformV(0.5f),}));
		cubeVertices.at(13) = TPVertexNormalised({ 0.5f,  0.5f, -0.5f}, normalise({0.f,  1.f,  0.f,}), normalise({letterCube.transformU(0.f),  letterCube.transformV(1.0f),}));
		cubeVertices.at(14) = TPVertexNormalised({-0.5f,  0.5f, -0.5f}, normalise({0.f,  1.f,  0.f,}), normalise({letterCube.transformU(0.33f),letterCube.transformV(1.0f),}));
		cubeVertices.at(15) = TPVertexNormalised({-0.5f,  0.5f,  0.5f}, normalise({0.f,  1.f,  0.f,}), normalise({letterCube.transformU(0.3f), letterCube.transformV(0.5f),}));
		cubeVertices.at(16) = TPVertexNormalised({-0.5f,  0.5f,  0.5f}, normalise({-1.f,  0.f,  0.f,}), normalise({letterCube.transformU(0.66f),letterCube.transformV(0.5f),}));
		cubeVertices.at(17) = TPVertexNormalised({-0.5f,  0.5f, -0.5f}, normalise({-1.f,  0.f,  0.f,}), normalise({letterCube.transformU(0.33f),letterCube.transformV(0.5f),}));
		cubeVertices.at(18) = TPVertexNormalised({-0.5f, -0.5f, -0.5f}, normalise({-1.f,  0.f,  0.f,}), normalise({letterCube.transformU(0.33f),letterCube.transformV(1.0f),}));
		cubeVertices.at(19) = TPVertexNormalised({-0.5f, -0.5f,  0.5f}, normalise({-1.f,  0.f,  0.f,}), normalise({letterCube.transformU(0.66f),letterCube.transformV(1.0f),}));
		cubeVertices.at(20) = TPVertexNormalised({ 0.5f, -0.5f, -0.5f}, normalise({1.f,  0.f,  0.f,}), normalise({letterCube.transformU(1.0f), letterCube.transformV(1.0f),}));
		cubeVertices.at(21) = TPVertexNormalised({ 0.5f,  0.5f, -0.5f}, normalise({1.f,  0.f,  0.f,}), normalise({letterCube.transformU(1.0f), letterCube.transformV(0.5f),}));
		cubeVertices.at(22) = TPVertexNormalised({ 0.5f,  0.5f,  0.5f}, normalise({1.f,  0.f,  0.f,}), normalise({letterCube.transformU(0.66f),letterCube.transformV(0.5f),}));
		cubeVertices.at(23) = TPVertexNormalised({ 0.5f, -0.5f,  0.5f}, normalise({1.f,  0.f,  0.f,}), normalise({letterCube.transformU(0.66f),letterCube.transformV(1.0f)}));


	
		std::vector<FCVertex> pyramidVertices(16);
		pyramidVertices.at(0) = FCVertex({-0.5f, -0.5f, -0.5f}, pack({0.8f, 0.2f, 0.8f}));
		pyramidVertices.at(1) = FCVertex({ 0.5f, -0.5f, -0.5f}, pack({0.8f, 0.2f, 0.8f}));
		pyramidVertices.at(2) = FCVertex({ 0.5f, -0.5f,  0.5f}, pack({0.8f, 0.2f, 0.8f}));
		pyramidVertices.at(3) = FCVertex({-0.5f, -0.5f,  0.5f}, pack({0.8f, 0.2f, 0.8f}));
		pyramidVertices.at(4) = FCVertex({-0.5f, -0.5f, -0.5f}, pack({0.2f, 0.8f, 0.2f}));
		pyramidVertices.at(5) = FCVertex({-0.5f, -0.5f,  0.5f}, pack({0.2f, 0.8f, 0.2f}));
		pyramidVertices.at(6) = FCVertex({ 0.0f,  0.5f,  0.0f}, pack({0.2f, 0.8f, 0.2f}));
		pyramidVertices.at(7) = FCVertex({-0.5f, -0.5f,  0.5f}, pack({1.0f, 0.0f, 0.f }));
		pyramidVertices.at(8) = FCVertex({ 0.5f, -0.5f,  0.5f}, pack({1.0f, 0.0f, 0.f }));
		pyramidVertices.at(9) = FCVertex({ 0.0f,  0.5f,  0.0f}, pack({1.0f, 0.0f, 0.f }));
		pyramidVertices.at(10) = FCVertex({ 0.5f, -0.5f, 0.5f}, pack({0.8f, 0.8f, 0.2f}));
		pyramidVertices.at(11) = FCVertex({ 0.5f, -0.5f,-0.5f}, pack({0.8f, 0.8f, 0.2f}));										 
		pyramidVertices.at(12) = FCVertex({ 0.0f,  0.5f, 0.0f}, pack({0.8f, 0.8f, 0.2f}));
		pyramidVertices.at(13) = FCVertex({ 0.5f, -0.5f,-0.5f}, pack({ 0.f, 0.2f, 1.0f}));
		pyramidVertices.at(14) = FCVertex({-0.5f, -0.5f,-0.5f}, pack({ 0.f, 0.2f, 1.0f}));
		pyramidVertices.at(15) = FCVertex({ 0.0f,  0.5f, 0.0f}, pack({ 0.f, 0.2f, 1.0f}));

		//float pyramidVertices[6 * 16] =  {					  
		//	//	 <------ Pos ------>  <--- colour ---> 
		//		-0.5f, -0.5f, -0.5f,  0.8f, 0.2f, 0.8f, //  square Magneta
		//		 0.5f, -0.5f, -0.5f,  0.8f, 0.2f, 0.8f,
		//		 0.5f, -0.5f,  0.5f,  0.8f, 0.2f, 0.8f,
		//		-0.5f, -0.5f,  0.5f,  0.8f, 0.2f, 0.8f,

		//		-0.5f, -0.5f, -0.5f,  0.2f, 0.8f, 0.2f,  //triangle Green
		//		-0.5f, -0.5f,  0.5f,  0.2f, 0.8f, 0.2f,
		//		 0.0f,  0.5f,  0.0f,  0.2f, 0.8f, 0.2f,

		//		-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.f, //triangle Red
		//		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.f,
		//		 0.0f,  0.5f,  0.0f,  1.0f, 0.0f, 0.f,

		//		 0.5f, -0.5f,  0.5f,  0.8f, 0.8f, 0.2f, //  triangle Yellow
		//		 0.5f, -0.5f, -0.5f,  0.8f, 0.8f, 0.2f,
		//		 0.0f,  0.5f,  0.0f,  0.8f, 0.8f, 0.2f,

		//		 0.5f, -0.5f, -0.5f,  0.f, 0.2f, 1.0f,//  triangle Blue
		//		-0.5f, -0.5f, -0.5f,  0.f, 0.2f, 1.0f,
		//		 0.0f,  0.5f,  0.0f,  0.f, 0.2f, 1.0f
		//};
			/*float cubeVertices[8 * 24] = {
				 //	 <------ Pos ------>  <--- normal --->  <---------------------- UV -------------------------->
				 0.5f,  0.5f, -0.5f,  0.f,  0.f, -1.f,  letterCube.transformU(0.f),   letterCube.transformV(0.f),
				 0.5f, -0.5f, -0.5f,  0.f,  0.f, -1.f,  letterCube.transformU(0.f),   letterCube.transformV(0.5f),
				-0.5f, -0.5f, -0.5f,  0.f,  0.f, -1.f,  letterCube.transformU(0.33f), letterCube.transformV(0.5f),
				-0.5f,  0.5f, -0.5f,  0.f,  0.f, -1.f,  letterCube.transformU(0.33f), letterCube.transformV(0.f),
				-0.5f, -0.5f, 0.5f,   0.f,  0.f,  1.f,  letterCube.transformU(0.33f), letterCube.transformV(0.5f),
				 0.5f, -0.5f, 0.5f,   0.f,  0.f,  1.f,  letterCube.transformU(0.66f), letterCube.transformV(0.5f),
				 0.5f,  0.5f, 0.5f,   0.f,  0.f,  1.f,  letterCube.transformU(0.66f), letterCube.transformV(0.f),
				-0.5f,  0.5f, 0.5f,   0.f,  0.f,  1.f,  letterCube.transformU(0.33),  letterCube.transformV(0.f),
				-0.5f, -0.5f, -0.5f,  0.f, -1.f,  0.f,  letterCube.transformU(1.f),   letterCube.transformV(0.f),
				 0.5f, -0.5f, -0.5f,  0.f, -1.f,  0.f,  letterCube.transformU(0.66f), letterCube.transformV(0.f),
				 0.5f, -0.5f, 0.5f,   0.f, -1.f,  0.f,  letterCube.transformU(0.66f), letterCube.transformV(0.5f),
				-0.5f, -0.5f, 0.5f,   0.f, -1.f,  0.f,  letterCube.transformU(1.0f),  letterCube.transformV(0.5f),
				 0.5f,  0.5f, 0.5f,   0.f,  1.f,  0.f,  letterCube.transformU(0.f),   letterCube.transformV(0.5f),
				 0.5f,  0.5f, -0.5f,  0.f,  1.f,  0.f,  letterCube.transformU(0.f),   letterCube.transformV(1.0f),
				-0.5f,  0.5f, -0.5f,  0.f,  1.f,  0.f,  letterCube.transformU(0.33f), letterCube.transformV(1.0f),
				-0.5f,  0.5f, 0.5f,   0.f,  1.f,  0.f,  letterCube.transformU(0.3f),  letterCube.transformV(0.5f),
				-0.5f,  0.5f, 0.5f,  -1.f,  0.f,  0.f,  letterCube.transformU(0.66f), letterCube.transformV(0.5f),
				-0.5f,  0.5f, -0.5f, -1.f,  0.f,  0.f,  letterCube.transformU(0.33f), letterCube.transformV(0.5f),
				-0.5f, -0.5f, -0.5f, -1.f,  0.f,  0.f,  letterCube.transformU(0.33f), letterCube.transformV(1.0f),
				-0.5f, -0.5f, 0.5f,  -1.f,  0.f,  0.f,  letterCube.transformU(0.66f), letterCube.transformV(1.0f),
				 0.5f, -0.5f, -0.5f,  1.f,  0.f,  0.f,  letterCube.transformU(1.0f),  letterCube.transformV(1.0f),
				 0.5f,  0.5f, -0.5f,  1.f,  0.f,  0.f,  letterCube.transformU(1.0f),  letterCube.transformV(0.5f),
				 0.5f,  0.5f, 0.5f,   1.f,  0.f,  0.f,  letterCube.transformU(0.66f), letterCube.transformV(0.5f),
				 0.5f, -0.5f, 0.5f,   1.f,  0.f,  0.f,  letterCube.transformU(0.66f), letterCube.transformV(1.0f)
		};*/


		//float cubeVertices[8 * 24] = {
		//	//	 <------ Pos ------>  <--- normal --->  <-------------------------- UV -------------------------->
		//		 0.5f,  0.5f, -0.5f,  0.f,  0.f, -1.f,  0.f,    0.f,
		//		 0.5f, -0.5f, -0.5f,  0.f,  0.f, -1.f,  0.f,   0.5f,
		//		-0.5f, -0.5f, -0.5f,  0.f,  0.f, -1.f,  0.33f, 0.5f,
		//		-0.5f,  0.5f, -0.5f,  0.f,  0.f, -1.f,  0.33f,  0.f,											  
		//		-0.5f, -0.5f, 0.5f,   0.f,  0.f,  1.f,  0.33f, 0.5f,
		//		 0.5f, -0.5f, 0.5f,   0.f,  0.f,  1.f,  0.66f, 0.5f,
		//		 0.5f,  0.5f, 0.5f,   0.f,  0.f,  1.f,  0.66f,  0.f,
		//		-0.5f,  0.5f, 0.5f,   0.f,  0.f,  1.f,  0.33,   0.f,									
		//		-0.5f, -0.5f, -0.5f,  0.f, -1.f,  0.f,  1.f,    0.f,
		//		 0.5f, -0.5f, -0.5f,  0.f, -1.f,  0.f,  0.66f,  0.f,
		//		 0.5f, -0.5f, 0.5f,   0.f, -1.f,  0.f,  0.66f, 0.5f,
		//		-0.5f, -0.5f, 0.5f,   0.f, -1.f,  0.f,  1.0f,  0.5f,											
		//		 0.5f,  0.5f, 0.5f,   0.f,  1.f,  0.f,  0.f,   0.5f,
		//		 0.5f,  0.5f, -0.5f,  0.f,  1.f,  0.f,  0.f,   1.0f,
		//		-0.5f,  0.5f, -0.5f,  0.f,  1.f,  0.f,  0.33f, 1.0f,
		//		-0.5f,  0.5f, 0.5f,   0.f,  1.f,  0.f,  0.3f,  0.5f,												
		//		-0.5f,  0.5f, 0.5f,  -1.f,  0.f,  0.f,  0.66f, 0.5f,
		//		-0.5f,  0.5f, -0.5f, -1.f,  0.f,  0.f,  0.33f, 0.5f,
		//		-0.5f, -0.5f, -0.5f, -1.f,  0.f,  0.f,  0.33f, 1.0f,
		//		-0.5f, -0.5f, 0.5f,  -1.f,  0.f,  0.f,  0.66f, 1.0f,
		//		 0.5f, -0.5f, -0.5f,  1.f,  0.f,  0.f,  1.0f,  1.0f,
		//		 0.5f,  0.5f, -0.5f,  1.f,  0.f,  0.f,  1.0f,  0.5f,
		//		 0.5f,  0.5f, 0.5f,   1.f,  0.f,  0.f,  0.66f, 0.5f,
		//		 0.5f, -0.5f, 0.5f,   1.f,  0.f,  0.f,  0.66f, 1.0f
		//};

		uint32_t pyramidIndices[3 * 6] =
		{
			0, 1, 2,
			2, 3, 0,
			4, 5, 6,
			7, 8, 9,
			10, 11, 12,
			13, 14, 15
		};

		uint32_t cubeIndices[3 * 12] = {
			0, 1, 2,
			2, 3, 0,
			4, 5, 6,
			6, 7, 4,
			8, 9, 10,
			10, 11, 8,
			12, 13, 14,
			14, 15, 12,
			16, 17, 18,
			18, 19, 16,
			20, 21, 22,
			22, 23, 20
		};
#pragma endregion 

#pragma region GL_BUFFERS	

		std::shared_ptr<VertexArray> cubeVAO;
		std::shared_ptr<VertexBuffer> cubeVBO;
		std::shared_ptr<IndexBuffer> cubeIBO;

		cubeVAO.reset(VertexArray::create());

		cubeVBO.reset(VertexBuffer::create(cubeVertices.data(), sizeof(TPVertexNormalised) * cubeVertices.size(), TPVertexNormalised::getLayout()));

		cubeIBO.reset(IndexBuffer::create(cubeIndices, 36));
		
		cubeVAO->addVertexBuffer(cubeVBO);
		cubeVAO->setIndexBuffer(cubeIBO);

		std::shared_ptr<VertexArray> pyramidVAO;
		std::shared_ptr<VertexBuffer>pyramidVBO;
		std::shared_ptr<IndexBuffer> pyramidIBO;

		pyramidVAO.reset(VertexArray::create());

		pyramidVBO.reset(VertexBuffer::create(pyramidVertices.data(), sizeof(FCVertex) * pyramidVertices.size(), FCVertex::getLayout()));

		pyramidIBO.reset(IndexBuffer::create(pyramidIndices, 18));

		pyramidVAO->addVertexBuffer(pyramidVBO);
		pyramidVAO->setIndexBuffer(pyramidIBO);
		
#pragma endregion

#pragma region SHADERS

		std::shared_ptr<Shader> FCShader;
		FCShader.reset(Shader::create("./assets/shaders/flatColour.glsl"));

		std::shared_ptr<Shader> TPShader;
		TPShader.reset(Shader::create("./assets/shaders/texturedPhong.glsl"));

#pragma endregion 

		//old camera ubo
		/*uint32_t cameraUBO;

		UniformBufferLayout camLayout = { {"u_projection", ShaderDataType::Mat4}, {"u_view", ShaderDataType::Mat4} };

		glGenBuffers(1, &cameraUBO);
		glBindBuffer(GL_UNIFORM_BUFFER, cameraUBO);
		glBufferData(GL_UNIFORM_BUFFER, camLayout.getStride(), nullptr, GL_DYNAMIC_DRAW);
		glBindBufferRange(GL_UNIFORM_BUFFER, blockNumber, cameraUBO, 0, camLayout.getStride());

		uint32_t blockIndex = glGetUniformBlockIndex(FCShader->getRenderID(), "b_camera");
		glUniformBlockBinding(FCShader->getRenderID(), blockIndex, blockNumber);

		blockIndex = glGetUniformBlockIndex(TPShader->getRenderID(), "b_camera");
		glUniformBlockBinding(TPShader->getRenderID(), blockIndex, blockNumber);


		auto element = *camLayout.begin();
		glBufferSubData(GL_UNIFORM_BUFFER, element.m_offset, element.m_size, glm::value_ptr(projection));

		element = *(camLayout.begin()+1);
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));*/

		//old light ubo
		/*glm::vec3 lightColour(1.f, 1.f, 1.f);
		glm::vec3 lightPosition(1.f, 4.f, 6.f);
		glm::vec3 viewPosition(0.f, 0.f, 0.f);

		uint32_t lightsUBO;
		uint32_t lightDataSize = sizeof(glm::vec4) * 3;

		glGenBuffers(1, &lightsUBO);
		glBindBuffer(GL_UNIFORM_BUFFER, lightsUBO);
		glBufferData(GL_UNIFORM_BUFFER, lightDataSize, nullptr, GL_DYNAMIC_DRAW);
		glBindBufferRange(GL_UNIFORM_BUFFER, blockNumber, lightsUBO, 0, lightDataSize);

		uint32_t blockIndex = glGetUniformBlockIndex(TPShader->getRenderID(), "b_light");
		glUniformBlockBinding(TPShader->getRenderID(), blockIndex, blockNumber);

		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::vec3), glm::value_ptr(lightColour));
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4), sizeof(glm::vec3), glm::value_ptr(lightPosition));
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4) * 2, sizeof(glm::vec3), glm::value_ptr(viewPosition));*/

		uint32_t blockNumber = 0;

		//Camera UBO
		UniformBufferLayout camLayout = { {"u_projection", ShaderDataType::Mat4}, {"u_view", ShaderDataType::Mat4} };

		std::shared_ptr<UniformBuffer> cameraUBO;
		cameraUBO.reset(UniformBuffer::create(camLayout));

		cameraUBO->attackShaderBlock(FCShader, "b_camera");
		cameraUBO->attackShaderBlock(TPShader, "b_camera");

		glm::mat4 view = glm::lookAt(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0., 0.f, -1), glm::vec3(0., 1.f, 0.f));
		glm::mat4 projection = glm::perspective(glm::radians(45.f), 1080.f / 800.f, 0.1f, 100.f);

		cameraUBO->uploadData("u_projection", glm::value_ptr(projection));
		cameraUBO->uploadData("u_view", glm::value_ptr(view));

		blockNumber++; //finish camera ubo block

		// Light UBO
		UniformBufferLayout lightLayout = { {"u_lightColour", ShaderDataType::Float3}, {"u_lightPos", ShaderDataType::Float3}, {"u_viewPos", ShaderDataType::Float3} };
		
		std::shared_ptr<UniformBuffer> lightUBO;
		lightUBO.reset(UniformBuffer::create(lightLayout));

		lightUBO->attackShaderBlock(TPShader, "b_light");

		glm::vec3 lightColour(1.f, 1.f, 1.f);
		glm::vec3 lightPosition(1.f, 4.f, 6.f);
		glm::vec3 viewPosition(0.f, 0.f, 0.f);

		lightUBO->uploadData("u_lightColour", glm::value_ptr(lightColour));
		lightUBO->uploadData("u_lightPos", glm::value_ptr(lightPosition));
		lightUBO->uploadData("u_viewPos", glm::value_ptr(viewPosition));

		blockNumber++;

		
		glm::mat4 models[3];
		models[0] = glm::translate(glm::mat4(1.0f), glm::vec3(-2.f, 0.f, -6.f));
		models[1] = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, -6.f));
		models[2] = glm::translate(glm::mat4(1.0f), glm::vec3(2.f, 0.f, -6.f));
		
		glEnable(GL_DEPTH_TEST);
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

		float timestep = 0.f;

		while (m_running)
		{
				timestep = m_timer->getElapsedTime();
				m_timer->reset();	

				//if (InputPoller::isKeyPressed(65)) Log::error("A is pressed");
				//if (InputPoller::isMouseButtonPressed(0)) Log::error("Left mouse button is pressed");


				//Do frame stuff
				for (auto& model : models) { model = glm::rotate(model, timestep, glm::vec3(0.f, 1.0, 0.f)); }

				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				GLuint uniformLocation;

				//Pyramid
				glUseProgram(FCShader->getRenderID());
				glBindVertexArray(pyramidVAO->getRenderID());
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pyramidIBO->getRenderID());

				uniformLocation = glGetUniformLocation(FCShader->getRenderID(), "u_model");
				glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(models[0]));

				glDrawElements(GL_TRIANGLES, pyramidVAO->getDrawCount() , GL_UNSIGNED_INT, nullptr);

				//Cube with letters texture
				glUseProgram(TPShader->getRenderID());
				glBindVertexArray(cubeVAO->getRenderID());
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeIBO->getRenderID());

				uniformLocation = glGetUniformLocation(TPShader->getRenderID(), "u_model");
				glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(models[1]));

				glBindTexture(GL_TEXTURE_2D, letterAndNumbertexture->getRenderID());
				uniformLocation = glGetUniformLocation(TPShader->getRenderID(), "u_texData");
				glUniform1i(uniformLocation, 0);

				glDrawElements(GL_TRIANGLES, cubeVAO->getDrawCount(), GL_UNSIGNED_INT, nullptr);

				//Cube with numbers texture
				uniformLocation = glGetUniformLocation(TPShader->getRenderID(), "u_model");
				glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(models[2]));

				//glBindTexture(GL_TEXTURE_2D, numberTexture->getRenderID());

				glDrawElements(GL_TRIANGLES, cubeVAO->getDrawCount(), GL_UNSIGNED_INT, nullptr);
				
				m_window->onUpdate(timestep);
				
		};


	}
		
}
