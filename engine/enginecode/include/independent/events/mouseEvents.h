/* \file mouseEvents.h*/

#pragma once

#include "event.h"
#include "glm/glm.hpp"

namespace Engine
{

	/**
    \class MouseEvent - The base mouse event class
    */
	class MouseEvent : public Event
	{
		inline virtual int32_t getCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; }
	};


	/**
	\class MouseButtonPressedEvent - The mouse button press event class
	*/
	class MouseButtonPressedEvent : public MouseEvent
	{
	private:
		int32_t m_button;

	public:
		MouseButtonPressedEvent(int32_t button) :
			m_button(button)
		{} //!< Default constructor

		static EventType getStaticType() { return EventType::MouseButtonPressed; } //!< Return static type
		inline virtual EventType getEventType() const override { return getStaticType(); } //!< Get the event type
		inline int32_t getButton() const { return m_button; } //!< Get which button is pressed

	};


	/**
    \class MouseButtonReleasedEvent - The mouse button release event class
    */
	class MouseButtonReleasedEvent : public MouseEvent
	{
	private:
		int32_t m_button;

	public:
		MouseButtonReleasedEvent(int32_t button) :
			m_button(button)
		{} //!< Default constructor

		static EventType getStaticType() { return EventType::MouseButtonReleased; } //!< Return static type
		inline virtual EventType getEventType() const override { return getStaticType(); } //!< Get the event type
		inline int32_t getButton() const { return m_button; } //!< Get which button is released
	};


	/**
    \class MouseMovedEvent - The mouse move event class
    */
	class MouseMovedEvent : public MouseEvent
	{
		
	private:
		float m_mouseX;
		float m_mouseY;

	public:
		MouseMovedEvent(float x, float y) :
			m_mouseX(x),
			m_mouseY(y)
		{} //!< Default constructor

		static EventType getStaticType() { return EventType::MouseMoved; } //!< Return static type
		inline virtual EventType getEventType() const override { return getStaticType(); } //!< Get the event type
		inline float getX() const { return m_mouseX; }
		inline float getY() const { return m_mouseY; }
		glm::vec2 getPos() const { return glm::vec2(m_mouseX, m_mouseY); }

	};


	/**
    \class MouseScrolledEvent - The mouse scroll event class
    */
	class MouseScrolledEvent : public MouseEvent
	{

	private:
		float m_offsetX;
		float m_offsetY;

	public:
		static EventType getStaticType() { return EventType::MouseScrolled; } //!< Return static type
		inline virtual EventType getEventType() const override { return getStaticType(); } //!< Get the event type
		inline float getOffsetX() const { return m_offsetX; } //!< Get the X offset
		inline float getOffsetY() const { return m_offsetY; } //!< Get the Y offset
		
	};



}
