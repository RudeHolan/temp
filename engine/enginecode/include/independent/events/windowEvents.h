/* \file windowsEvents.h*/

#pragma once

#include "event.h"

#include <glm/glm.hpp>

namespace Engine
{	
	/**
	\class WindowsEvent - The base windows event class
	*/
	class WindowEvent : public Event 
	{
	public:
		virtual int32_t getCategoryFlags() const override { return EventCategoryWindow; } //!< Get the event category flag
	};


	/**
    \class WindowCloseEvent - The window close event class
    */
	class WindowCloseEvent : public WindowEvent
	{

	public:
		static EventType getStaticType() { return EventType::WindowClose; } //!< Return static type
		inline virtual EventType getEventType() const override { return EventType::WindowClose; }; //!< Get the event type
	};


	/**
    \class WindowResizeEvent - The window resize event class
    */
	class WindowResizeEvent : public WindowEvent
	{

	private:
		int32_t m_width;   //!< Window width after resize
		int32_t m_height;  //!< Window height after resize

	public:
		WindowResizeEvent(int32_t width, int32_t height) :
			m_width(width),
			m_height(height) 
		{} //!< Constructor

		static EventType getStaticType() { return EventType::WindowResize; } //!< Return static type
		inline virtual EventType getEventType() const override { return EventType::WindowResize; }; //!< Get the event type
		inline int32_t getWidth() const { return m_width; } //!< Get the width of the window
		inline int32_t getHeight() const { return m_height; } //!< Get the height of the window
		inline glm::ivec2 getSize() const { return { m_width, m_height }; } //!< Get the size of the window
	};


	/**
	\class WindowFocusEvent - The window focus event class
	*/
	class WindowFocusEvent : public WindowEvent
	{
	private: 
		int focus; //!< this int is 1 when the window is focused and 0 when the window has lost focus

	public:
		WindowFocusEvent(int f) : focus(f) {}; //!< Constructor
		static EventType getStaticType() { return EventType::WindowFocus; } //!< Return static type
		inline virtual EventType getEventType() const override { return EventType::WindowFocus; }; //!< Get the event type
		inline int getFocus() const { return focus; } //!< Check if the window is on focus
	};


	/**
	\class WindowsLostFocusEvent - The windows lost focus event class
	*/
	class WindowLostFocusEvent : public WindowEvent
	{
	private:
		int focus; //!< this int is 1 when the window is focused and 0 when the window has lost focus

	public:
		WindowLostFocusEvent(int f) : focus(f) {} //!< Constructor 
		static EventType getStaticType() { return EventType::WindowLostFocus; } //!< Return static type
		inline virtual EventType getEventType() const override { return EventType::WindowLostFocus; }; //!< Get the event type
		inline int getFocus() const { return focus; } //!< Check if the window has lost focus
	};


	/**
	\class WindowsMoveEvent - The windows move event class
	*/
	class WindowMoveEvent : public WindowEvent
	{
	private:
		int32_t m_posX; //!< Position X of the window
		int32_t m_posY; //!< Position Y of the window

	public:
		WindowMoveEvent(int32_t x, int32_t y) :
			m_posX(x),
			m_posY(y)
		{} //!< Constructor

		static EventType getStaticType() { return EventType::WindowMoved; } //!< Return static type
		inline virtual EventType getEventType() const override { return EventType::WindowMoved; }; //!< Get the event type
		inline int32_t getPosX() const { return m_posX; } //!< Get the X position of the window
		inline int32_t getPosY() const { return m_posY; } //!< Get the Y position of the window
		inline glm::ivec2 getPos() const { return { m_posX, m_posY }; } //!< Get both the X and Y position of the window 
	};



}