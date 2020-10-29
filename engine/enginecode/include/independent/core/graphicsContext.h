/* \file graphicsContext.h */

#pragma once

namespace
{
	class GraphicsContext
	{
	public:
		virtual void init() = 0; //!< Initialize the graphics context for the given windowing API
		virtual void swapBuffers() = 0; //!< Swap the front and back buffer (double buffering) 
	};
}