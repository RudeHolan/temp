#pragma once

#include<gtest/gtest.h>
#include "events/eventHandler.h"

class MockApplication
{
private:
	bool onClose(Engine::WindowCloseEvent& e)
	{
		e.handle(true);
		return e.isHandled();
	}

public:
	Engine::EventHandler m_handler;

	void setCallback()
	{
		m_handler.setOnWindowCloseCallback(std::bind(&MockApplication::onClose, this, std::placeholders::_1));
	}
};