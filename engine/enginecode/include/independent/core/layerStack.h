#pragma once

#include "layer.h"

namespace Engine
{
	class LayerStack
	{
	private:
		std::vector<std::shared_ptr<Layer>> m_stack;

	public:
		LayerStack() { m_stack.reserve(10); }
		~LayerStack();

		void push(Layer* layer);
		void pop();

		void update(float ts);
		void render();

		void onKeyPressed(KeyPressEvent& e);
		void onKeyReleased(KeyReleaseEvent& e);
		void onMousePressed(MouseButtonPressEvent& e);
		void onMouseReleased(MouseButtonReleaseEvent& e);
		void onMouseWheel(MouseScrollEvent& e);
		void onMouseMoved(MouseMoveEvent& e);

		void setActive(const char* layerName, bool activeState);
		void setDisplayed(const char* layerName, bool displayState);
		void setFocused(const char* layerName, bool focusedState);
		void setAllActive(bool activeState);
		void setAllDisplayed(bool displayState);
		void setAllFocused(bool focusState);		

		std::vector<std::shared_ptr<Layer>>::iterator begin() { return m_stack.begin(); }
		std::vector<std::shared_ptr<Layer>>::iterator end() { return m_stack.end(); }
		std::vector<std::shared_ptr<Layer>>::reverse_iterator rbegin() { return m_stack.rbegin(); }
		std::vector<std::shared_ptr<Layer>>::reverse_iterator rend() { return m_stack.rend(); }

		std::vector<std::shared_ptr<Layer>>::const_iterator begin() const { return m_stack.begin(); }
		std::vector<std::shared_ptr<Layer>>::const_iterator end() const { return m_stack.end(); }
		std::vector<std::shared_ptr<Layer>>::const_reverse_iterator rbegin() const { return m_stack.rbegin(); }
		std::vector<std::shared_ptr<Layer>>::const_reverse_iterator rend() const { return m_stack.rend(); }



	};
}