#include "engine_pch.h"
#include "cameras/cameraController.h"
#include "..\..\..\include\independent\core\layerStack.h"

namespace Engine
{
	LayerStack::~LayerStack()
	{
		for (uint32_t i = m_stack.size(); i > 0; i--) pop();
	}

	void LayerStack::push(Layer* layer)
	{
		layer->onAttach();
		std::shared_ptr<Layer> temp(layer);
		m_stack.push_back(temp);
	}

	void LayerStack::pop()
	{
		m_stack.back()->onDetach();
		m_stack.pop_back();
	}

	void LayerStack::update(float ts)
	{
		for (auto& layer : m_stack) layer->onUpdate(ts);
	}

	void LayerStack::render()
	{
		for (auto& layer : m_stack) layer->onRender();
	}

	void LayerStack::onKeyPressed(KeyPressEvent& e)
	{
		for (auto& layer : m_stack) if (layer->isFocused() && !e.isHandled()) layer->onKeyPressed(e);
	}

	void LayerStack::onKeyReleased(KeyReleaseEvent& e)
	{
		for (auto& layer : m_stack) if (layer->isFocused() && !e.isHandled()) layer->onKeyReleased(e);
	}

	void LayerStack::onMousePressed(MouseButtonPressEvent& e)
	{
		for (auto& layer : m_stack) if (layer->isFocused() && !e.isHandled()) layer->onMousePressed(e);
	}

	void LayerStack::onMouseReleased(MouseButtonReleaseEvent& e)
	{
		for (auto& layer : m_stack) if (layer->isFocused() && !e.isHandled()) layer->onMouseReleased(e);
	}

	void LayerStack::onMouseMoved(MouseMoveEvent& e)
	{
		for (auto& layer : m_stack) if (layer->isFocused() && !e.isHandled()) layer->onMouseMoved(e);
	}

	void LayerStack::setActive(const char* layerName, bool activeState)
	{
		for (auto& layer : m_stack) if (layer->getName() == layerName) layer->setActive(activeState);
	}

	void LayerStack::setDisplayed(const char* layerName, bool displayState)
	{
		for (auto& layer : m_stack) if (layer->getName() == layerName) layer->setDisplayed(displayState);
	}

	void LayerStack::setFocused(const char* layerName, bool focusedState)
	{
		for (auto& layer : m_stack) if (layer->getName() == layerName) layer->setFocused(focusedState);
	}

	void LayerStack::setAllActive(bool activeState)
	{
		for (auto& layer : m_stack) layer->setActive(activeState);

	}

	void LayerStack::setAllDisplayed(bool displayState)
	{
		for (auto& layer : m_stack) layer->setDisplayed(displayState);
	}

	void LayerStack::setAllFocused(bool focusState)
	{
		for (auto& layer : m_stack) layer->setFocused(focusState);
	}
}