/** \file GLFWWindowImpl.h*/

#pragma once

#include "core/window.h"

#include "GLFW/glfw3.h"

namespace Engine 
{
	/**\class GLFWWindowImpl 
	* Implementation of a window using GLFW
	*/
	class GLFWWindowImpl : public Window
	{
	private:
		WindowProperties m_props; //!< Properties
		GLFWwindow* m_native; //!< Native GLFW window
		float m_aspectRatio; //!< Aspect ratio


	public:
		GLFWWindowImpl(const WindowProperties& properties); //!< Constructor
		virtual void init(const WindowProperties& properties) override; //!< Initialise the window
		virtual void close() override; //!< Close the window
		//virtual ~Window() {}; //!< Virtual distructor
		virtual void onUpdate(float timestep) override;  //!< The update function
		virtual void setVSync(bool VSync) override; //!< Set VSync on
		inline virtual unsigned int getWidth() const override { return m_props.m_width; } //!< Get the width
		inline virtual unsigned int getHeight() const override { return m_props.m_height; } //!< Get the height
		inline virtual void* getNativeWindow() const override { return m_native; } //!< Get the native window
		inline virtual bool isFullScreen() const override { return m_props.m_isFullscreen; } //!< Check if fullscreen mode is on
		inline virtual bool isVSync() const override { return m_props.m_isVSync; } //!< Check if VSync is on
	};


}
