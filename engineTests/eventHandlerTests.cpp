#pragma once

#include "eventHandlerTests.h"

TEST(EventHandler, onClose) {

	MockApplication app;

	Engine::WindowCloseEvent e;

	bool handledBefore = e.isHandled();
	auto& onCloseFunctionDefault = app.m_handler.m_getOnWindowCloseCallback();
	onCloseFunctionDefault(e);
	bool handledDefault = e.isHandled();

	app.setCallback();
	auto& onCloseFunction = app.m_handler.m_getOnWindowCloseCallback();
	onCloseFunction(e);
	bool handledAfter = e.isHandled();

	EXPECT_EQ(false, handledDefault);
	EXPECT_EQ(handledBefore, handledDefault);
	EXPECT_NE(handledBefore, handledAfter);
	EXPECT_EQ(handledAfter, true);
	EXPECT_EQ(handledBefore, false);
}