/* \file windowsEvents.h*/

#pragma once

#include "event.h"

#include <glm/glm.hpp>

namespace Engine
{	
	/**
	\class WindowsEvent - The base windows event class
	*/
	class WindowEvent : Event 
	{
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
		{} //!< Default constructor

		static EventType getStaticType() { return EventType::WindowResize; } //!< Return static type
		inline virtual EventType getEventType() const override { return EventType::WindowResize; }; //!< Get the event type
		inline int32_t getWidth() const { return m_width; }
		inline int32_t getHeight() const { return m_height; }
		inline glm::ivec2 getSize() const { return { m_width, m_height }; }
	};


	/**
	\class WindowFocusEvent - The window focus event class
	*/
	class WindowFocusEvent : public WindowEvent
	{
	public:
		WindowFocusEvent() {} //!< Default constructor
		static EventType getStaticType() { return EventType::WindowFocus; } //!< Return static type
		inline virtual EventType getEventType() const override { return EventType::WindowResize; }; //!< Get the event type
	};


	/**
	\class WindowsLostFocusEvent - The windows lost focus event class
	*/
	class WindowLostFocusEvent : public WindowEvent
	{
	public:
		WindowLostFocusEvent() {} //!< Default constructor
		static EventType getStaticType() { return EventType::WindowLostFocus; } //!< Return static type
		inline virtual EventType getEventType() const override { return EventType::WindowResize; }; //!< Get the event type
	};


	/**
	\class WindowsMoveEvent - The windows move event class
	*/
	class WindowMoveEvent : public WindowEvent
	{
	private:
		int32_t m_posX;
		int32_t m_posY;

	public:
		WindowMoveEvent(int32_t x, int32_t y) :
			m_posX(x),
			m_posY(y)
		{} //!< Default constructor

		static EventType getStaticType() { return EventType::WindowMoved; } //!< Return static type
		inline virtual EventType getEventType() const override { return EventType::WindowResize; }; //!< Get the event type
		inline int32_t getPosX() const { return m_posX; }
		inline int32_t getPosY() const { return m_posY; }
		inline glm::ivec2 getPos() const { return { m_posX, m_posY }; }
	};



}