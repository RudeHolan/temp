/*\ file GLFW_OpenGL_GC.h*/

#pragma once


#include "core/graphicsContext.h"

namespace Engine
{
	/**
    \class GLFW_OpenGL_GC
    ** \brief A class that initializes the window context 
    */
	class GLFW_OpenGL_GC : public GraphicsContext
	{
	private:
		GLFWwindow* m_window; //!< Pointer to GLFW window

	public:
		GLFW_OpenGL_GC(GLFWwindow* win) : m_window(win) {}; //!< Constructor
		virtual void init() override; //!< Initialize the graphics context for the given windowing API
		virtual void swapBuffers() override; //!< Swap the front and back buffer (double buffering) 
	};
}