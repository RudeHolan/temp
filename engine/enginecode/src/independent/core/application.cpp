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

#include "platform/OpenGL/OpenGLVertexArray.h"
#include "platform/OpenGL/OpenGLShader.h"
#include "platform/OpenGL/OpenGLTexture.h"

#include "rendering/indexBuffer.h"#
#include "rendering/vertexBuffer.h"
#include "rendering/vertexArray.h"
#include "rendering/subTexture.h"

namespace Engine {
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



	bool Application::onClose(WindowCloseEvent & e)
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


	void Application::run()
	{

#pragma region TEXTURES

		std::shared_ptr<OpenGLTexture> letterTexture;
		letterTexture.reset(new OpenGLTexture("assets/textures/letterAndNumberCube.png"));

		std::shared_ptr<OpenGLTexture> numberTexture;
		numberTexture.reset(new OpenGLTexture("assets/textures/numberCube.png"));

		SubTexture letterCube(letterTexture, { 0.f,0.f }, { 1.0f,0.5f });
		SubTexture numberCube(letterTexture, { 0.f,0.5f }, { 1.0f,1.0f });

#pragma endregion

#pragma region RAW_DATA

		float cubeVertices[8 * 24] = {
			//	 <------ Pos ------>  <--- normal --->  <-------------------------- UV -------------------------->
				 0.5f,  0.5f, -0.5f,  0.f,  0.f, -1.f,  numberCube.transformU(0.f),   numberCube.transformV(0.f),
				 0.5f, -0.5f, -0.5f,  0.f,  0.f, -1.f,  numberCube.transformU(0.f),   numberCube.transformV(0.5f),
				-0.5f, -0.5f, -0.5f,  0.f,  0.f, -1.f,  numberCube.transformU(0.33f), numberCube.transformV(0.5f),
				-0.5f,  0.5f, -0.5f,  0.f,  0.f, -1.f,  numberCube.transformU(0.33f), numberCube.transformV(0.f),
																					  
				-0.5f, -0.5f, 0.5f,   0.f,  0.f,  1.f,  numberCube.transformU(0.33f), numberCube.transformV(0.5f),
				 0.5f, -0.5f, 0.5f,   0.f,  0.f,  1.f,  numberCube.transformU(0.66f), numberCube.transformV(0.5f),
				 0.5f,  0.5f, 0.5f,   0.f,  0.f,  1.f,  numberCube.transformU(0.66f), numberCube.transformV(0.f),
				-0.5f,  0.5f, 0.5f,   0.f,  0.f,  1.f,  numberCube.transformU(0.33),  numberCube.transformV(0.f),
																					
				-0.5f, -0.5f, -0.5f,  0.f, -1.f,  0.f,  numberCube.transformU(1.f),   numberCube.transformV(0.f),
				 0.5f, -0.5f, -0.5f,  0.f, -1.f,  0.f,  numberCube.transformU(0.66f), numberCube.transformV(0.f),
				 0.5f, -0.5f, 0.5f,   0.f, -1.f,  0.f,  numberCube.transformU(0.66f), numberCube.transformV(0.5f),
				-0.5f, -0.5f, 0.5f,   0.f, -1.f,  0.f,  numberCube.transformU(1.0f),  numberCube.transformV(0.5f),
																					
				 0.5f,  0.5f, 0.5f,   0.f,  1.f,  0.f,  numberCube.transformU(0.f),   numberCube.transformV(0.5f),
				 0.5f,  0.5f, -0.5f,  0.f,  1.f,  0.f,  numberCube.transformU(0.f),   numberCube.transformV(1.0f),
				-0.5f,  0.5f, -0.5f,  0.f,  1.f,  0.f,  numberCube.transformU(0.33f), numberCube.transformV(1.0f),
				-0.5f,  0.5f, 0.5f,   0.f,  1.f,  0.f,  numberCube.transformU(0.3f),  numberCube.transformV(0.5f),
																					
				-0.5f,  0.5f, 0.5f,  -1.f,  0.f,  0.f,  numberCube.transformU(0.66f), numberCube.transformV(0.5f),
				-0.5f,  0.5f, -0.5f, -1.f,  0.f,  0.f,  numberCube.transformU(0.33f), numberCube.transformV(0.5f),
				-0.5f, -0.5f, -0.5f, -1.f,  0.f,  0.f,  numberCube.transformU(0.33f), numberCube.transformV(1.0f),
				-0.5f, -0.5f, 0.5f,  -1.f,  0.f,  0.f,  numberCube.transformU(0.66f), numberCube.transformV(1.0f),
																				
				 0.5f, -0.5f, -0.5f,  1.f,  0.f,  0.f,  numberCube.transformU(1.0f),  numberCube.transformV(1.0f),
				 0.5f,  0.5f, -0.5f,  1.f,  0.f,  0.f,  numberCube.transformU(1.0f),  numberCube.transformV(0.5f),
				 0.5f,  0.5f, 0.5f,   1.f,  0.f,  0.f,  numberCube.transformU(0.66f), numberCube.transformV(0.5f),
				 0.5f, -0.5f, 0.5f,   1.f,  0.f,  0.f,  numberCube.transformU(0.66f), numberCube.transformV(1.0f)
		};

		float pyramidVertices[6 * 16] = {
			//	 <------ Pos ------>  <--- colour ---> 
				-0.5f, -0.5f, -0.5f,  0.8f, 0.2f, 0.8f, //  square Magneta
				 0.5f, -0.5f, -0.5f,  0.8f, 0.2f, 0.8f,
				 0.5f, -0.5f,  0.5f,  0.8f, 0.2f, 0.8f,
				-0.5f, -0.5f,  0.5f,  0.8f, 0.2f, 0.8f,

				-0.5f, -0.5f, -0.5f,  0.2f, 0.8f, 0.2f,  //triangle Green
				-0.5f, -0.5f,  0.5f,  0.2f, 0.8f, 0.2f,
				 0.0f,  0.5f,  0.0f,  0.2f, 0.8f, 0.2f,

				-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.f, //triangle Red
				 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.f,
				 0.0f,  0.5f,  0.0f,  1.0f, 0.0f, 0.f,

				 0.5f, -0.5f,  0.5f,  0.8f, 0.8f, 0.2f, //  triangle Yellow
				 0.5f, -0.5f, -0.5f,  0.8f, 0.8f, 0.2f,
				 0.0f,  0.5f,  0.0f,  0.8f, 0.8f, 0.2f,

				 0.5f, -0.5f, -0.5f,  0.f, 0.2f, 1.0f,//  triangle Blue
				-0.5f, -0.5f, -0.5f,  0.f, 0.2f, 1.0f,
				 0.0f,  0.5f,  0.0f,  0.f, 0.2f, 1.0f
		};

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

		BufferLayout cubeBL = { ShaderDataType::Float3,ShaderDataType::Float3, ShaderDataType::Float2 };
		cubeVBO.reset(VertexBuffer::create(cubeVertices, sizeof(cubeVertices), cubeBL));

		cubeIBO.reset(IndexBuffer::create(cubeIndices, 36));
		
		cubeVAO->addVertexBuffer(cubeVBO);
		cubeVAO->setIndexBuffer(cubeIBO);

		std::shared_ptr<VertexArray> pyramidVAO;
		std::shared_ptr<VertexBuffer>pyramidVBO;
		std::shared_ptr<IndexBuffer> pyramidIBO;

		pyramidVAO.reset(VertexArray::create());

		BufferLayout pyramidBL = { ShaderDataType::Float3, ShaderDataType::Float3 };
		pyramidVBO.reset(VertexBuffer::create(pyramidVertices, sizeof(pyramidVertices), pyramidBL));

		pyramidIBO.reset(IndexBuffer::create(pyramidIndices, 18));

		pyramidVAO->addVertexBuffer(pyramidVBO);
		pyramidVAO->setIndexBuffer(pyramidIBO);
		
#pragma endregion

#pragma region SHADERS

		std::shared_ptr<OpenGLShader> FCShader;
		FCShader.reset(new OpenGLShader("./assets/shaders/flatColour.glsl"));

		std::shared_ptr<OpenGLShader> TPShader;
		TPShader.reset(new OpenGLShader("./assets/shaders/texturedPhong.glsl"));

#pragma endregion 




		glm::mat4 view = glm::lookAt( glm::vec3(0.f,0.f,0.f), glm::vec3(0.,0.f,-1), glm::vec3(0.,1.f,0.f));
		glm::mat4 projection = glm::perspective(glm::radians(45.f), 1080.f / 800.f, 0.1f, 100.f);
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

				uniformLocation = glGetUniformLocation(FCShader->getRenderID(), "u_projection");
				glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(projection));

				uniformLocation = glGetUniformLocation(FCShader->getRenderID(), "u_view");
				glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(view));

				uniformLocation = glGetUniformLocation(FCShader->getRenderID(), "u_model");
				glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(models[0]));

				glDrawElements(GL_TRIANGLES, pyramidVAO->getDrawCount() , GL_UNSIGNED_INT, nullptr);


				//Cube with letters texture
				glUseProgram(TPShader->getRenderID());
				glBindVertexArray(cubeVAO->getRenderID());
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeIBO->getRenderID());

				uniformLocation = glGetUniformLocation(TPShader->getRenderID(), "u_model");
				glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(models[1]));

				uniformLocation = glGetUniformLocation(TPShader->getRenderID(), "u_view");
				glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(view));

				uniformLocation = glGetUniformLocation(TPShader->getRenderID(), "u_projection");
				glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(projection));

				uniformLocation = glGetUniformLocation(TPShader->getRenderID(), "u_lightColour");
				glUniform3f(uniformLocation, 1.f, 1.f, 1.f);

				uniformLocation = glGetUniformLocation(TPShader->getRenderID(), "u_lightPos");
				glUniform3f(uniformLocation, 1.f, 4.f, 6.f);

				uniformLocation = glGetUniformLocation(TPShader->getRenderID(), "u_viewPos");
				glUniform3f(uniformLocation, 0.f, 0.f, 0.f);

				glBindTexture(GL_TEXTURE_2D, letterTexture->getRenderID());
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
