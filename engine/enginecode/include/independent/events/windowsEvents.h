/* \file windowsEvents.h*/

#pragma once

#include "event.h"

#include <glm/glm.hpp>

namespace Engine
{

	/**
    \class WindowCloseEvent - The window close event class
    */
	class WindowCloseEvent : public Event
	{

	public:
		static EventType getStaticType() { return EventType::WindowClose; } //!< Return static type
		inline virtual EventType getEventType() const override { return EventType::WindowClose; }; //!< Get the event type
		virtual int32_t getCategoryFlags() const override { return EventCategoryWindow; } //!< Get the event category flag

	};


	/**
    \class WindowResizeEvent - The window resize event class
    */
	class WindowsResizeEvent : public Event
	{

	private:
		int32_t m_width;   //!< Window width after resize
		int32_t m_height;  //!< Window height after resize

	public:
		WindowsResizeEvent(int32_t width, int32_t height) :
			m_width(width),
			m_height(height) 
		{} //!< Default constructor
		static EventType getStaticType() { return EventType::WindowResize; } //!< Return static type
		inline virtual EventType getEventType() const override { return EventType::WindowResize; }; //!< Get the event type
		virtual int32_t getCategoryFlags() const override { return EventCategoryWindow; } //!< Get the event category flag

	};


	/**
	\class WindowFocusEvent - The window focus event class
	*/
	class WindowsFocusEvent : public Event
	{


	};


	/**
	\class WindowsLostFocusEvent - The windows lost focus event class
	*/
	class WindowsLostFocusEvent : public Event
	{

	};


	/**
	\class WindowsMoveEvent - The windows move event class
	*/
	class WindowsMoveEvent : public Event
	{

	};



}