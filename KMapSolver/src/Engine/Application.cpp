#include "Engine/Application.h"
using namespace WI;

float Application::m_fDTime = 0.0f;
sf::Clock Application::m_appClock;
sf::Color Application::m_clearColor;
States Application::m_eAppState;

WI::Application::Application()
{
	m_appWindow = new sf::RenderWindow(sf::VideoMode(800u, 600u), "APP");
	m_event = new sf::Event;
	m_appWindow->setView(m_defaultView);
	m_defaultView.setCenter(m_defaultView.getSize().x / 2.0f, m_defaultView.getSize().y / 2.0f);
	m_eAppState = States::Main;
	m_clearColor = sf::Color::Black;
}

Application::Application(const sf::Vector2u &resolution, const std::string &appName, const sf::Color &clearColor)
{
	m_appWindow = new sf::RenderWindow(sf::VideoMode(resolution.x, resolution.y), appName);
	m_event = new sf::Event;
	m_appWindow->setView(m_defaultView);
	m_defaultView.setCenter(m_defaultView.getSize().x / 2.0f, m_defaultView.getSize().y / 2.0f);
	m_eAppState = States::Main;
	m_clearColor = clearColor;
}

uint32_t Application::GetScreenWidth()
{
	return uint32_t(m_appWindow->getSize().x);
}

uint32_t Application::GetScreenHeight()
{
	return uint32_t(m_appWindow->getSize().y);
}

void Application::HandleEvents_()
{
	while (m_appWindow->pollEvent(*m_event))
	{
		if (m_event->type == sf::Event::Closed)
			m_eAppState = States::Exit;
		/*if (m_event->type == sf::Event::Resized)
		{
			m_defaultView.setSize(sf::Vector2f(m_appWindow->getSize()));
			std::cout << "Here\n";
		}*/
		HandleEvents();
	}
}
void Application::HandleEvents()
{
}

void Application::Update()
{
}

void Application::Draw()
{
}

void Application::CheckStates()
{
}

void Application::CheckOGStates()
{
	if (m_eAppState == States::Exit)
		m_appWindow->close();
}

void Application::Run()
{
	while (m_appWindow->isOpen())
	{
		m_fDTime = m_appClock.restart().asSeconds();
		HandleEvents_();
		CheckStates();
		CheckOGStates();
		Update();

		m_appWindow->setView(m_defaultView);
		m_appWindow->clear(m_clearColor);
		Draw();
		m_appWindow->display();
	}
}
void Application::SetClearColor(const sf::Color &clearColor)
{
	m_clearColor = clearColor;
}

Application::~Application()
{
	if (m_appWindow != nullptr)
		delete m_appWindow;
	if (m_event != nullptr)
		delete m_event;
}