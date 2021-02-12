#pragma once

#include <string>
#include "window.h"

namespace Engine
{
	class Layer
	{
	protected:
		const char* m_name; //!< Name, useful for debugging
		bool m_isDisplayed = true;
		bool m_isActive = true;
		bool m_isFocused = true;

	public:
		Layer(const char* name) : m_name(name) {};

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onRender() {}
		virtual void onUpdate(float ts) {}

		inline const char* getName() const { return m_name; }
		inline void setDisplayed(bool displayStatus) { m_isDisplayed = displayStatus; }
		inline void setActive(bool activeStatus) { m_isActive = activeStatus; }
		inline void setFocused(bool focusStatus) { m_isFocused = focusStatus; }
		inline const bool isDisplayed() const { return m_isDisplayed; }
		inline const bool isActive() const { return m_isActive; }
		inline const bool isFocused() const { return m_isFocused; }
	};
}