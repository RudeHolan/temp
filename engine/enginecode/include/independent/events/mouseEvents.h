/* \file mouseEvents.h*/

#pragma once

#include "event.h"
#include "glm/glm.hpp"

namespace Engine
{

	/**
    \class MouseEvent 
	** \brief The base mouse event class
    */
	class MouseEvent : public Event
	{
		inline virtual int32_t getCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; } //!< Gets the category flags 
	};


	/**
	\class MouseButtonPressEvent 
	** \brief The mouse button press event class
	*/
	class MouseButtonPressEvent : public MouseEvent
	{
	private:
		int32_t m_button; //!< The keycode of a mouse button

	public:
		MouseButtonPressEvent(int32_t button) :
			m_button(button)
		{} //!< Constructor

		static EventType getStaticType() { return EventType::MouseButtonPressed; } //!< Return static type
		inline virtual EventType getEventType() const override { return getStaticType(); } //!< Get the event type
		inline int32_t getButton() const { return m_button; } //!< Get which button is pressed

	};


	/**
    \class MouseButtonReleaseEvent
	** \brief The mouse button release event class
    */
	class MouseButtonReleaseEvent : public MouseEvent
	{
	private:
		int32_t m_button; //!< The keycode of a mouse button

	public:
		MouseButtonReleaseEvent(int32_t button) :
			m_button(button)
		{} //!< Constructor

		static EventType getStaticType() { return EventType::MouseButtonReleased; } //!< Return static type
		inline virtual EventType getEventType() const override { return getStaticType(); } //!< Get the event type
		inline int32_t getButton() const { return m_button; } //!< Get which button is released
	};


	/**
    \class MouseMoveEvent
	** \brief The mouse move event class
    */
	class MouseMoveEvent : public MouseEvent
	{
		
	private:
		float m_mouseX; //!< mouse X position
		float m_mouseY; //!< mouse Y position

	public:
		MouseMoveEvent(float x, float y) :
			m_mouseX(x),
			m_mouseY(y)
		{} //!< Constructor

		static EventType getStaticType() { return EventType::MouseMoved; } //!< Return static type
		inline virtual EventType getEventType() const override { return getStaticType(); } //!< Get the event type
		inline float getX() const { return m_mouseX; } //!< Get the mouse X position
		inline float getY() const { return m_mouseY; } //!< Get the mouse Y position
		glm::vec2 getPos() const { return glm::vec2(m_mouseX, m_mouseY); } //!< Get the mouse position in vec2 format

	};


	/**
    \class MouseScrollEvent
	** \brief The mouse scroll event class
    */
	class MouseScrollEvent : public MouseEvent
	{

	private:
		float m_offsetX;  //!<The X offset of the mouse scroll wheel 
		float m_offsetY;  //!<The Y offset of the mouse scroll wheel 

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
