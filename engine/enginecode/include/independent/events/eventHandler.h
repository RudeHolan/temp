/** \file eventHandler.h*/
#pragma once


#include "events.h"
#include <functional>

namespace Engine
{
	class EventHandler
	{
	private:
		std::function<bool(WindowCloseEvent&)> m_onWindowCloseCallback = std::bind(&EventHandler::defaultOnWindowClose, this, std::placeholders::_1);
		std::function<bool(WindowResizeEvent&)> m_onWindowResizeCallback = std::bind(&EventHandler::defaultOnWindowResize, this, std::placeholders::_1);
		std::function<bool(WindowFocusEvent&)> m_onWindowFocusCallback = std::bind(&EventHandler::defaultOnWindowFocus, this, std::placeholders::_1);
		std::function<bool(WindowLostFocusEvent&)> m_onWindowLostFocusCallback = std::bind(&EventHandler::defaultOnWindowLostFocus, this, std::placeholders::_1);
		std::function<bool(WindowMoveEvent&)> m_onWindowMoveCallback = std::bind(&EventHandler::defaultOnWindowMove, this, std::placeholders::_1);

		std::function<bool(KeyPressEvent&)> m_onKeyPressCallback = std::bind(&EventHandler::defaultOnKeyPress, this, std::placeholders::_1);
		std::function<bool(KeyReleaseEvent&)> m_onKeyReleaseCallback = std::bind(&EventHandler::defaultOnKeyRelease, this, std::placeholders::_1);
		std::function<bool(KeyTypeEvent&)> m_onKeyTypeCallback = std::bind(&EventHandler::defaultOnKeyType, this, std::placeholders::_1);

		std::function<bool(MouseButtonPressEvent&)> m_onMouseButtonPressCallback = std::bind(&EventHandler::defaultOnMouseButtonPresse, this, std::placeholders::_1);
		std::function<bool(MouseButtonReleaseEvent&)> m_onMouseButtonReleaseCallback = std::bind(&EventHandler::defaultOnMouseButtonRelease, this, std::placeholders::_1);
		std::function<bool(MouseMoveEvent&)> m_onMouseMoveCallback = std::bind(&EventHandler::defaultOnMouseMove, this, std::placeholders::_1);
		std::function<bool(MouseScrollEvent&)> m_onMouseScrollCallback = std::bind(&EventHandler::defaultOnMouseScroll, this, std::placeholders::_1);

		bool defaultOnWindowClose(WindowCloseEvent&) { return false; }
		bool defaultOnWindowResize(WindowResizeEvent&) { return false; }
		bool defaultOnWindowFocus(WindowFocusEvent&) { return false; }
		bool defaultOnWindowLostFocus(WindowLostFocusEvent&) { return false; }
		bool defaultOnWindowMove(WindowMoveEvent&) { return false; }

		bool defaultOnKeyPress(KeyPressEvent&) { return false; }
		bool defaultOnKeyRelease(KeyReleaseEvent&) { return false; }
		bool defaultOnKeyType(KeyTypeEvent&) { return false; }

		bool defaultOnMouseButtonPresse(MouseButtonPressEvent&) { return false; }
		bool defaultOnMouseButtonRelease(MouseButtonReleaseEvent&) { return false; }
		bool defaultOnMouseMove(MouseMoveEvent&) { return false; }
		bool defaultOnMouseScroll(MouseScrollEvent&) { return false; }

	public:
		void setOnWindowCloseCallback(const std::function<bool(WindowCloseEvent&)>& fn) { m_onWindowCloseCallback = fn; }
		void setOnWindowResizeCallback(const std::function<bool(WindowResizeEvent&)>& fn) { m_onWindowResizeCallback = fn; }
		void setOnWindowFocusCallback(const std::function<bool(WindowFocusEvent&)>& fn) { m_onWindowFocusCallback = fn; }
		void setOnWindowLostFocusCallback(const std::function<bool(WindowLostFocusEvent&)>& fn) { m_onWindowLostFocusCallback = fn; }
		void setOnWindowMoveCallback(const std::function<bool(WindowMoveEvent&)>& fn) { m_onWindowMoveCallback = fn; }

		void setOnKeyPressCallback(const std::function<bool(KeyPressEvent&)>& fn) { m_onKeyPressCallback = fn; }
		void setOnKeyReleaseCallback(const std::function<bool(KeyReleaseEvent&)>& fn) { m_onKeyReleaseCallback = fn; }
		void setOnKeyTypeCallback(const std::function<bool(KeyTypeEvent&)>& fn) { m_onKeyTypeCallback = fn; }
		
		void setOnMouseButtonPressCallback(const std::function<bool(MouseButtonPressEvent&)>& fn) { m_onMouseButtonPressCallback = fn; }
		void setOnMouseButtonReleaseCallback(const std::function<bool(MouseButtonReleaseEvent&)>& fn) { m_onMouseButtonReleaseCallback = fn; }
		void setOnMouseMoveCallback(const std::function<bool(MouseMoveEvent&)>& fn) { m_onMouseMoveCallback = fn; }
		void setOnMouseScrollCallback(const std::function<bool(MouseScrollEvent&)>& fn) { m_onMouseScrollCallback = fn; }

		std::function<bool(WindowCloseEvent&)> m_getOnWindowCloseCallback() { return m_onWindowCloseCallback; };
		std::function<bool(WindowResizeEvent&)> m_getOnWindowResizeCallback() { return m_onWindowResizeCallback; };
		std::function<bool(WindowFocusEvent&)> m_getOnWindowFocusCallback() { return m_onWindowFocusCallback; };
		std::function<bool(WindowLostFocusEvent&)> m_getOnWindowLostFocusCallback() { return m_onWindowLostFocusCallback; };
		std::function<bool(WindowMoveEvent&)> m_getOnWindowMoveCallback() { return m_onWindowMoveCallback; };

		std::function<bool(KeyPressEvent&)> m_getOnKeyPressCallback() { return m_onKeyPressCallback; };
		std::function<bool(KeyReleaseEvent&)> m_getOnKeyReleaseCallback() { return m_onKeyReleaseCallback; };
		std::function<bool(KeyTypeEvent&)> m_getOnKeyTypeCallback() { return m_onKeyTypeCallback; };

		std::function<bool(MouseButtonPressEvent&)> m_getOnMouseButtonPressCallback() { return m_onMouseButtonPressCallback; };
		std::function<bool(MouseButtonReleaseEvent&)> m_getOnMouseButtonReleaseCallback() { return m_onMouseButtonReleaseCallback; };
		std::function<bool(MouseMoveEvent&)> m_getOnMouseMoveCallback() { return m_onMouseMoveCallback; };
		std::function<bool(MouseScrollEvent&)> m_getOnMouseScrollCallback() { return m_onMouseScrollCallback; };

	};
}
