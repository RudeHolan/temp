/** \file application.cpp
*/

#include "engine_pch.h"
#include <glad/glad.h>
#include "core/application.h"

#ifdef NG_PLATFORM_WINDOWS
#include "platform/GLFW/GLFWSystem.h"
#endif

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "platform/OpenGL/OpenGLVertexArray.h"

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
#pragma region RAW_DATA

		float cubeVertices[8 * 24] = {
			//	 <------ Pos ------>  <--- normal --->  <-- UV -->
				 0.5f,  0.5f, -0.5f,  0.f,  0.f, -1.f,  0.f,   0.f,
				 0.5f, -0.5f, -0.5f,  0.f,  0.f, -1.f,  0.f,   0.5f,
				-0.5f, -0.5f, -0.5f,  0.f,  0.f, -1.f,  0.33f, 0.5f,
				-0.5f,  0.5f, -0.5f,  0.f,  0.f, -1.f,  0.33f, 0.f,

				-0.5f, -0.5f, 0.5f,   0.f,  0.f,  1.f,  0.33f, 0.5f,
				 0.5f, -0.5f, 0.5f,   0.f,  0.f,  1.f,  0.66f, 0.5f,
				 0.5f,  0.5f, 0.5f,   0.f,  0.f,  1.f,  0.66f, 0.f,
				-0.5f,  0.5f, 0.5f,   0.f,  0.f,  1.f,  0.33,  0.f,

				-0.5f, -0.5f, -0.5f,  0.f, -1.f,  0.f,  1.f,   0.f,
				 0.5f, -0.5f, -0.5f,  0.f, -1.f,  0.f,  0.66f, 0.f,
				 0.5f, -0.5f, 0.5f,   0.f, -1.f,  0.f,  0.66f, 0.5f,
				-0.5f, -0.5f, 0.5f,   0.f, -1.f,  0.f,  1.0f,  0.5f,

				 0.5f,  0.5f, 0.5f,   0.f,  1.f,  0.f,  0.f,   0.5f,
				 0.5f,  0.5f, -0.5f,  0.f,  1.f,  0.f,  0.f,   1.0f,
				-0.5f,  0.5f, -0.5f,  0.f,  1.f,  0.f,  0.33f, 1.0f,
				-0.5f,  0.5f, 0.5f,   0.f,  1.f,  0.f,  0.3f,  0.5f,

				-0.5f,  0.5f, 0.5f,  -1.f,  0.f,  0.f,  0.66f, 0.5f,
				-0.5f,  0.5f, -0.5f, -1.f,  0.f,  0.f,  0.33f, 0.5f,
				-0.5f, -0.5f, -0.5f, -1.f,  0.f,  0.f,  0.33f, 1.0f,
				-0.5f, -0.5f, 0.5f,  -1.f,  0.f,  0.f,  0.66f, 1.0f,

				 0.5f, -0.5f, -0.5f,  1.f,  0.f,  0.f,  1.0f,  1.0f,
				 0.5f,  0.5f, -0.5f,  1.f,  0.f,  0.f,  1.0f,  0.5f,
				 0.5f,  0.5f, 0.5f,   1.f,  0.f,  0.f,  0.66f, 0.5f,
				 0.5f, -0.5f, 0.5f,   1.f,  0.f,  0.f,  0.66f, 1.0f
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

		std::shared_ptr<OpenGLVertexArray> cubeVAO;
		std::shared_ptr<OpenGLVertexBuffer> cubeVBO;
		std::shared_ptr<OpenGLIndexBuffer> cubeIBO;

		cubeVAO.reset(new OpenGLVertexArray);

		BufferLayout cubeBL = { ShaderDataType::Float3,ShaderDataType::Float3, ShaderDataType::Float2 };
		cubeVBO.reset(new OpenGLVertexBuffer(cubeVertices, sizeof(cubeVertices), cubeBL));

		cubeIBO.reset(new OpenGLIndexBuffer(cubeIndices, 36));
		
		cubeVAO->addVertexBuffer(cubeVBO);
		cubeVAO->setIndexBuffer(cubeIBO);

		std::shared_ptr<OpenGLVertexArray> pyramidVAO;
		std::shared_ptr<OpenGLVertexBuffer>pyramidVBO;
		std::shared_ptr<OpenGLIndexBuffer> pyramidIBO;

		pyramidVAO.reset(new OpenGLVertexArray);

		BufferLayout pyramidBL = { ShaderDataType::Float3, ShaderDataType::Float3 };
		pyramidVBO.reset(new OpenGLVertexBuffer(pyramidVertices, sizeof(pyramidVertices), pyramidBL));

		pyramidIBO.reset(new OpenGLIndexBuffer(pyramidIndices, 18));

		pyramidVAO->addVertexBuffer(pyramidVBO);
		pyramidVAO->setIndexBuffer(pyramidIBO);
		
#pragma endregion

#pragma region SHADERS
		std::string FCvertSrc = R"(
				#version 440 core
			
				layout(location = 0) in vec3 a_vertexPosition;
				layout(location = 1) in vec3 a_vertexColour;
				out vec3 fragmentColour;
				uniform mat4 u_model;
				uniform mat4 u_view;
				uniform mat4 u_projection;
				void main()
				{
					fragmentColour = a_vertexColour;
					gl_Position =  u_projection * u_view * u_model * vec4(a_vertexPosition,1);
				}
			)";

		std::string FCFragSrc = R"(
				#version 440 core
			
				layout(location = 0) out vec4 colour;
				in vec3 fragmentColour;
				void main()
				{
					colour = vec4(fragmentColour, 1.0);
				}
		)";

		std::string TPvertSrc = R"(
				#version 440 core
			
				layout(location = 0) in vec3 a_vertexPosition;
				layout(location = 1) in vec3 a_vertexNormal;
				layout(location = 2) in vec2 a_texCoord;
				out vec3 fragmentPos;
				out vec3 normal;
				out vec2 texCoord;
				uniform mat4 u_model;
				uniform mat4 u_view;
				uniform mat4 u_projection;
				void main()
				{
					fragmentPos = vec3(u_model * vec4(a_vertexPosition, 1.0));
					normal = mat3(transpose(inverse(u_model))) * a_vertexNormal;
					texCoord = vec2(a_texCoord.x, a_texCoord.y);
					gl_Position =  u_projection * u_view * u_model * vec4(a_vertexPosition,1.0);
				}
			)";

		std::string TPFragSrc = R"(
				#version 440 core
			
				layout(location = 0) out vec4 colour;
				in vec3 normal;
				in vec3 fragmentPos;
				in vec2 texCoord;
				uniform vec3 u_lightPos; 
				uniform vec3 u_viewPos; 
				uniform vec3 u_lightColour;
				uniform sampler2D u_texData;
				void main()
				{
					float ambientStrength = 0.4;
					vec3 ambient = ambientStrength * u_lightColour;
					vec3 norm = normalize(normal);
					vec3 lightDir = normalize(u_lightPos - fragmentPos);
					float diff = max(dot(norm, lightDir), 0.0);
					vec3 diffuse = diff * u_lightColour;
					float specularStrength = 0.8;
					vec3 viewDir = normalize(u_viewPos - fragmentPos);
					vec3 reflectDir = reflect(-lightDir, norm);  
					float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
					vec3 specular = specularStrength * spec * u_lightColour;  
					
					colour = vec4((ambient + diffuse + specular), 1.0) * texture(u_texData, texCoord);
				}
		)";



		uint32_t FCprogram, TPprogram;

		GLuint FCVertShader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* source = FCvertSrc.c_str();
		glShaderSource(FCVertShader, 1, &source, 0);
		glCompileShader(FCVertShader);

		GLint isCompiled = 0;
		glGetShaderiv(FCVertShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(FCVertShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(FCVertShader, maxLength, &maxLength, &infoLog[0]);
			Log::error("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteShader(FCVertShader);
			return;
		}

		GLuint FCFragShader = glCreateShader(GL_FRAGMENT_SHADER);

		source = FCFragSrc.c_str();
		glShaderSource(FCFragShader, 1, &source, 0);
		glCompileShader(FCFragShader);

		glGetShaderiv(FCFragShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(FCFragShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(FCFragShader, maxLength, &maxLength, &infoLog[0]);
			Log::error("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteShader(FCFragShader);
			glDeleteShader(FCVertShader);

			return;
		}

		FCprogram = glCreateProgram();
		glAttachShader(FCprogram, FCVertShader);
		glAttachShader(FCprogram, FCFragShader);
		glLinkProgram(FCprogram);

		GLint isLinked = 0;
		glGetProgramiv(FCprogram, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(FCprogram, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(FCprogram, maxLength, &maxLength, &infoLog[0]);
			Log::error("Shader linking error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteProgram(FCprogram);
			glDeleteShader(FCVertShader);
			glDeleteShader(FCFragShader);

			return;
		}

		glDetachShader(FCprogram, FCVertShader);
		glDetachShader(FCprogram, FCFragShader);


		GLuint TPVertShader = glCreateShader(GL_VERTEX_SHADER);

		source = TPvertSrc.c_str();
		glShaderSource(TPVertShader, 1, &source, 0);
		glCompileShader(TPVertShader);

		isCompiled = 0;
		glGetShaderiv(TPVertShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(TPVertShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(TPVertShader, maxLength, &maxLength, &infoLog[0]);
			Log::error("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteShader(TPVertShader);
			return;
		}

		GLuint TPFragShader = glCreateShader(GL_FRAGMENT_SHADER);

		source = TPFragSrc.c_str();
		glShaderSource(TPFragShader, 1, &source, 0);
		glCompileShader(TPFragShader);

		glGetShaderiv(TPFragShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(TPFragShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(TPFragShader, maxLength, &maxLength, &infoLog[0]);
			Log::error("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteShader(TPFragShader);
			glDeleteShader(TPVertShader);

			return;
		}

		TPprogram = glCreateProgram();
		glAttachShader(TPprogram, TPVertShader);
		glAttachShader(TPprogram, TPFragShader);
		glLinkProgram(TPprogram);

		isLinked = 0;
		glGetProgramiv(TPprogram, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(TPprogram, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(TPprogram, maxLength, &maxLength, &infoLog[0]);
			Log::error("Shader linking error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteProgram(TPprogram);
			glDeleteShader(TPVertShader);
			glDeleteShader(TPFragShader);

			return;
		}

		glDetachShader(TPprogram, TPVertShader);
		glDetachShader(TPprogram, TPFragShader);
#pragma endregion 

#pragma region TEXTURES

		uint32_t letterTexture, numberTexture;

		glGenTextures(1, &letterTexture);
		glBindTexture(GL_TEXTURE_2D, letterTexture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height, channels;


		unsigned char* data = stbi_load("assets/textures/letterCube.png", &width, &height, &channels, 0);
		if (data)
		{
			if (channels == 3) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			else if (channels == 4) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			else return;
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			Log::error("letterCube.png not found or location invalid");
			return;
		}
		stbi_image_free(data);

		glGenTextures(1, &numberTexture);
		glBindTexture(GL_TEXTURE_2D, numberTexture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		data = stbi_load("assets/textures/numberCube.png", &width, &height, &channels, 0);
		if (data)
		{
			if (channels == 3) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			else if (channels == 4) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			else return;
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			Log::error("numberCube.png not found or location invalid");
			return;
		}
		stbi_image_free(data);
#pragma endregion



		glm::mat4 view = glm::lookAt(
		    glm::vec3(0.f,0.f,0.f),
			glm::vec3(0.,0.f,-1),
			glm::vec3(0.,1.f,0.f)
		);
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

				GLuint location;

				//Pyramid
				glUseProgram(FCprogram);
				glBindVertexArray(pyramidVAO->getRenderID());
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pyramidIBO->getRenderID());

				location = glGetUniformLocation(FCprogram, "u_projection");
				glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projection));

				location = glGetUniformLocation(FCprogram, "u_view");
				glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(view));

				location = glGetUniformLocation(FCprogram, "u_model");
				glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(models[0]));

				glDrawElements(GL_TRIANGLES, pyramidVAO->getDrawCount() , GL_UNSIGNED_INT, nullptr);


				//Cube with letters texture
				glUseProgram(TPprogram);
				glBindVertexArray(cubeVAO->getRenderID());
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeIBO->getRenderID());

				location = glGetUniformLocation(TPprogram, "u_model");
				glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(models[1]));

				location = glGetUniformLocation(TPprogram, "u_view");
				glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(view));

				location = glGetUniformLocation(TPprogram, "u_projection");
				glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projection));

				location = glGetUniformLocation(TPprogram, "u_lightColour");
				glUniform3f(location, 1.f, 1.f, 1.f);

				location = glGetUniformLocation(TPprogram, "u_lightPos");
				glUniform3f(location, 1.f, 4.f, 6.f);

				location = glGetUniformLocation(TPprogram, "u_viewPos");
				glUniform3f(location, 0.f, 0.f, 0.f);

				glBindTexture(GL_TEXTURE_2D, letterTexture);
				location = glGetUniformLocation(TPprogram, "u_texData");
				glUniform1i(location, 0);

				glDrawElements(GL_TRIANGLES, cubeVAO->getDrawCount(), GL_UNSIGNED_INT, nullptr);

				//Cube with numbers texture
				location = glGetUniformLocation(TPprogram, "u_model");
				glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(models[2]));

				glBindTexture(GL_TEXTURE_2D, numberTexture);

				glDrawElements(GL_TRIANGLES, cubeVAO->getDrawCount(), GL_UNSIGNED_INT, nullptr);
				
				m_window->onUpdate(timestep);
				
		};

		glDeleteShader(FCprogram);
		glDeleteShader(TPprogram);

		glDeleteTextures(1, &letterTexture);
		glDeleteTextures(1, &numberTexture);

	}
		
}
