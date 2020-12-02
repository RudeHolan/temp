/* \file keyboardEvents.h*/

#pragma once

#include "event.h"
#include <inttypes.h>

namespace Engine
{
	/**
	\class KeyEvent - base Key event class/
	*/
	class KeyEvent : public Event
	{

	protected:
		int32_t m_keyCode;

	public:


		KeyEvent(int32_t keycode) :
			m_keyCode(keycode)
		{} //!< Default constructor


		inline int32_t getKeyCode() const { return m_keyCode; } //!< Get the key code
		virtual inline int32_t getCategoryFlags() const override { return EventCategoryKeyboard | EventCategoryInput; } //!< Get the event category flag

	};


	/**
	\class KeyPressEvent - The key press event
	*/
	class KeyPressEvent : public KeyEvent
	{

	private:
		int32_t m_repeatCount; //!< The repeat count of the pressed button

	public:
		
		KeyPressEvent(int32_t keycode, int32_t repeatCount) :
			KeyEvent(keycode),
			m_repeatCount(repeatCount)
		{} //!< Default constructor

		inline int32_t getRepeatCount() const { return m_repeatCount; } //!< Get the repeat count 
		static EventType getStaticType() { return EventType::KeyPressed; } //!< Return static type
		inline virtual EventType getEventType() const override { return getStaticType(); } //!< Get the event type

	};


	/**
    \class KeyReleaseEvent - The key release event
    */
	class KeyReleaseEvent : public KeyEvent
	{

	public:
		KeyReleaseEvent(int32_t keycode) : 
			KeyEvent(keycode)
		{} //!< Default constructor

		static EventType getStaticType() { return EventType::KeyReleased; } //!< Return static type
		inline virtual EventType getEventType() const override { return getStaticType(); } //!< Get the event type

	};


	/**
    \class KeyTypeEvent - The key type event
    */
	class KeyTypeEvent : public KeyEvent
	{
	public:
		KeyTypeEvent(int32_t keycode) :
			KeyEvent(keycode)
		{} //!< Default constructor

		static EventType getStaticType() { return EventType::KeyTyped; } //!< Return static type
		inline virtual EventType getEventType() const override { return getStaticType(); } //!< Get the event type

	};
}