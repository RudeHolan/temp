/* \file window.h */

#pragma once

#include "events/eventHandler.h"
#include<tuple>
#include"core/graphicsContext.h"

namespace Engine
{

	struct WindowProperties
	{
		char* m_title;
		uint32_t m_width;
		uint32_t m_height;
		bool m_isFullscreen;
		bool m_isVSync;

		//replace this using std::tuple
		WindowProperties(char* title = "My Window", uint32_t width = 800, uint32_t height = 600, bool isFullscreen = false) :
			m_title(title),
			m_width(width),
			m_height(height),
			m_isFullscreen(isFullscreen)
		{};
	};


	/**\class Window
    *Abstract windows base class. All implemented windows should code to this interface.
    */
	class Window
	{ 
	protected:
		EventHandler m_handler; //!< Event handler 
		std::shared_ptr<GraphicsContext> m_graphicsContext; // the graphics context

	public:
		virtual void init(const WindowProperties& properties) = 0; //!< Initialise the window
		virtual void close() = 0; //!< Close the window
		virtual ~Window() {}; //!< Virtual distructor
		virtual void onUpdate(float timestep) = 0;  //!< The update function
		virtual void setVSync(bool VSync) = 0; //!< Set VSync on
		virtual unsigned int getWidth() const = 0; //!< Get the width
		virtual unsigned int getHeight() const = 0; //!< Get the height
		virtual void* getNativeWindow() const = 0; //!< Get the native window
		virtual bool isFullScreen() const = 0; //!< Check if fullscreen mode is on
		virtual bool isVSync() const = 0; //!< Check if VSync is on

		inline EventHandler& getEventHandler() { return m_handler; } //!< Get the event handler
		
		static Window* create(const WindowProperties& properties = WindowProperties()); //!< Create a window



	};


}