/** \file eventHandler.h*/
#pragma once


#include "events.h"
#include <functional>

namespace Engine
{

	/**
    \class EventHandler 
	** \brief Handles all of the events
    */
	class EventHandler
	{
	private:
		std::function<bool(WindowCloseEvent&)> m_onWindowCloseCallback = std::bind(&EventHandler::defaultOnWindowClose, this, std::placeholders::_1);                 		 //!< The window close event callback 
		std::function<bool(WindowResizeEvent&)> m_onWindowResizeCallback = std::bind(&EventHandler::defaultOnWindowResize, this, std::placeholders::_1);					 //!< The window resize event callback
		std::function<bool(WindowFocusEvent&)> m_onWindowFocusCallback = std::bind(&EventHandler::defaultOnWindowFocus, this, std::placeholders::_1);						 //!< The window focus event callback
		std::function<bool(WindowLostFocusEvent&)> m_onWindowLostFocusCallback = std::bind(&EventHandler::defaultOnWindowLostFocus, this, std::placeholders::_1);			 //!< The window lost event focuscallback
		std::function<bool(WindowMoveEvent&)> m_onWindowMoveCallback = std::bind(&EventHandler::defaultOnWindowMove, this, std::placeholders::_1);							 //!< The window move event callback
																																											 
		std::function<bool(KeyPressEvent&)> m_onKeyPressCallback = std::bind(&EventHandler::defaultOnKeyPress, this, std::placeholders::_1);								 //!< The keyboard press event callback
		std::function<bool(KeyReleaseEvent&)> m_onKeyReleaseCallback = std::bind(&EventHandler::defaultOnKeyRelease, this, std::placeholders::_1);							 //!< The keyboard release event callback
		std::function<bool(KeyTypeEvent&)> m_onKeyTypeCallback = std::bind(&EventHandler::defaultOnKeyType, this, std::placeholders::_1);									 //!< The keyboard type event callback 
																																								
		std::function<bool(MouseButtonPressEvent&)> m_onMouseButtonPressCallback = std::bind(&EventHandler::defaultOnMouseButtonPresse, this, std::placeholders::_1);		 //!< The mouse button press event callback
		std::function<bool(MouseButtonReleaseEvent&)> m_onMouseButtonReleaseCallback = std::bind(&EventHandler::defaultOnMouseButtonRelease, this, std::placeholders::_1);	 //!< The mouse button release event callback
		std::function<bool(MouseMoveEvent&)> m_onMouseMoveCallback = std::bind(&EventHandler::defaultOnMouseMove, this, std::placeholders::_1);								 //!< The mouse move event callback
		std::function<bool(MouseScrollEvent&)> m_onMouseScrollCallback = std::bind(&EventHandler::defaultOnMouseScroll, this, std::placeholders::_1);						 //!< The mouse scroll event callback

		bool defaultOnWindowClose(WindowCloseEvent&) { return false; }				   //!< The default window close event callback state
		bool defaultOnWindowResize(WindowResizeEvent&) { return false; }			   //!< The default window resize event callback state
		bool defaultOnWindowFocus(WindowFocusEvent&) { return false; }				   //!< The default window focus event callback state
		bool defaultOnWindowLostFocus(WindowLostFocusEvent&) { return false; }		   //!< The default window lost event focuscallback state
		bool defaultOnWindowMove(WindowMoveEvent&) { return false; }				   //!< The default window move event callback state
																								 
		bool defaultOnKeyPress(KeyPressEvent&) { return false; }					   //!< The default keyboard press event callback state
		bool defaultOnKeyRelease(KeyReleaseEvent&) { return false; }				   //!< The default keyboard release event callback state
		bool defaultOnKeyType(KeyTypeEvent&) { return false; }						   //!< The default keyboard type event callback state
																								
		bool defaultOnMouseButtonPresse(MouseButtonPressEvent&) { return false; }	   //!< The default mouse button press event callback state
		bool defaultOnMouseButtonRelease(MouseButtonReleaseEvent&) { return false; }   //!< The default mouse button release event callback state
		bool defaultOnMouseMove(MouseMoveEvent&) { return false; }					   //!< The default mouse move event callback state
		bool defaultOnMouseScroll(MouseScrollEvent&) { return false; }				   //!< The default mouse scroll event callback state

	public:
		void setOnWindowCloseCallback(const std::function<bool(WindowCloseEvent&)>& fn) { m_onWindowCloseCallback = fn; }						 //!< Setting the on window close event callback 
		void setOnWindowResizeCallback(const std::function<bool(WindowResizeEvent&)>& fn) { m_onWindowResizeCallback = fn; }					 //!< Setting the on window resize event callback
		void setOnWindowFocusCallback(const std::function<bool(WindowFocusEvent&)>& fn) { m_onWindowFocusCallback = fn; }						 //!< Setting the on window focus event callback
		void setOnWindowLostFocusCallback(const std::function<bool(WindowLostFocusEvent&)>& fn) { m_onWindowLostFocusCallback = fn; }			 //!< Setting the on window lost event focuscallback
		void setOnWindowMoveCallback(const std::function<bool(WindowMoveEvent&)>& fn) { m_onWindowMoveCallback = fn; }							 //!< Setting the on window move event callback
																																					 
		void setOnKeyPressCallback(const std::function<bool(KeyPressEvent&)>& fn) { m_onKeyPressCallback = fn; }								 //!< Setting the on keyboard press event callback
		void setOnKeyReleaseCallback(const std::function<bool(KeyReleaseEvent&)>& fn) { m_onKeyReleaseCallback = fn; }							 //!< Setting the on keyboard release event callback
		void setOnKeyTypeCallback(const std::function<bool(KeyTypeEvent&)>& fn) { m_onKeyTypeCallback = fn; }									 //!< Setting the on keyboard type event callback 
																																					  
		void setOnMouseButtonPressCallback(const std::function<bool(MouseButtonPressEvent&)>& fn) { m_onMouseButtonPressCallback = fn; }		 //!< Setting the on mouse button press event callback
		void setOnMouseButtonReleaseCallback(const std::function<bool(MouseButtonReleaseEvent&)>& fn) { m_onMouseButtonReleaseCallback = fn; }	 //!< Setting the on mouse button release event callback
		void setOnMouseMoveCallback(const std::function<bool(MouseMoveEvent&)>& fn) { m_onMouseMoveCallback = fn; }								 //!< Setting the on mouse move event callback
		void setOnMouseScrollCallback(const std::function<bool(MouseScrollEvent&)>& fn) { m_onMouseScrollCallback = fn; }						 //!< Setting the on mouse scroll event callback

		std::function<bool(WindowCloseEvent&)> m_getOnWindowCloseCallback() { return m_onWindowCloseCallback; };						 //!< Get the on window close event callback 
		std::function<bool(WindowResizeEvent&)> m_getOnWindowResizeCallback() { return m_onWindowResizeCallback; };						 //!< Get the on window resize event callback
		std::function<bool(WindowFocusEvent&)> m_getOnWindowFocusCallback() { return m_onWindowFocusCallback; };						 //!< Get the on window focus event callback
		std::function<bool(WindowLostFocusEvent&)> m_getOnWindowLostFocusCallback() { return m_onWindowLostFocusCallback; };			 //!< Get the on window lost event focuscallback
		std::function<bool(WindowMoveEvent&)> m_getOnWindowMoveCallback() { return m_onWindowMoveCallback; };							 //!< Get the on window move event callback
																																			   			
		std::function<bool(KeyPressEvent&)> m_getOnKeyPressCallback() { return m_onKeyPressCallback; };									 //!< Get the on keyboard press event callback
		std::function<bool(KeyReleaseEvent&)> m_getOnKeyReleaseCallback() { return m_onKeyReleaseCallback; };							 //!< Get the on keyboard release event callback
		std::function<bool(KeyTypeEvent&)> m_getOnKeyTypeCallback() { return m_onKeyTypeCallback; };									 //!< Get the on keyboard type event callback 
																																			    		
		std::function<bool(MouseButtonPressEvent&)> m_getOnMouseButtonPressCallback() { return m_onMouseButtonPressCallback; };			 //!< Get the on mouse button press event callback
		std::function<bool(MouseButtonReleaseEvent&)> m_getOnMouseButtonReleaseCallback() { return m_onMouseButtonReleaseCallback; };	 //!< Get the on mouse button release event callback
		std::function<bool(MouseMoveEvent&)> m_getOnMouseMoveCallback() { return m_onMouseMoveCallback; };								 //!< Get the on mouse move event callback
		std::function<bool(MouseScrollEvent&)> m_getOnMouseScrollCallback() { return m_onMouseScrollCallback; };						 //!< Get the on mouse scroll event callback

	};
}
