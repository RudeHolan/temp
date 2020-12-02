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
	\class MouseButtonPressEvent - The mouse button press event class
	*/
	class MouseButtonPressEvent : public MouseEvent
	{
	private:
		int32_t m_button;

	public:
		MouseButtonPressEvent(int32_t button) :
			m_button(button)
		{} //!< Constructor

		static EventType getStaticType() { return EventType::MouseButtonPressed; } //!< Return static type
		inline virtual EventType getEventType() const override { return getStaticType(); } //!< Get the event type
		inline int32_t getButton() const { return m_button; } //!< Get which button is pressed

	};


	/**
    \class MouseButtonReleaseEvent - The mouse button release event class
    */
	class MouseButtonReleaseEvent : public MouseEvent
	{
	private:
		int32_t m_button;

	public:
		MouseButtonReleaseEvent(int32_t button) :
			m_button(button)
		{} //!< Constructor

		static EventType getStaticType() { return EventType::MouseButtonReleased; } //!< Return static type
		inline virtual EventType getEventType() const override { return getStaticType(); } //!< Get the event type
		inline int32_t getButton() const { return m_button; } //!< Get which button is released
	};


	/**
    \class MouseMoveEvent - The mouse move event class
    */
	class MouseMoveEvent : public MouseEvent
	{
		
	private:
		float m_mouseX;
		float m_mouseY;

	public:
		MouseMoveEvent(float x, float y) :
			m_mouseX(x),
			m_mouseY(y)
		{} //!< Constructor

		static EventType getStaticType() { return EventType::MouseMoved; } //!< Return static type
		inline virtual EventType getEventType() const override { return getStaticType(); } //!< Get the event type
		inline float getX() const { return m_mouseX; }
		inline float getY() const { return m_mouseY; }
		glm::vec2 getPos() const { return glm::vec2(m_mouseX, m_mouseY); }

	};


	/**
    \class MouseScrollEvent - The mouse scroll event class
    */
	class MouseScrollEvent : public MouseEvent
	{

	private:
		float m_offsetX;
		float m_offsetY;

	public:
		MouseScrollEvent(float xOffset, float yOffset) :
			m_offsetX(xOffset),
			m_offsetY(yOffset)
		{}//!< Constructor 

		static EventType getStaticType() { return EventType::MouseScrolled; } //!< Return static type
		inline virtual EventType getEventType() const override { return getStaticType(); } //!< Get the event type
		inline float getOffsetX() const { return m_offsetX; } //!< Get the X offset
		inline float getOffsetY() const { return m_offsetY; } //!< Get the Y offset
		
	};



}
