/** \file engineApp.cpp
*/
#include "engineApp.h"

engineApp::engineApp()
{
	m_layerStack.push(new UILayer("UI Layer"));
}

engineApp::~engineApp()
{

}

Engine::Application* Engine::startApplication()
{	
	return new engineApp();
}