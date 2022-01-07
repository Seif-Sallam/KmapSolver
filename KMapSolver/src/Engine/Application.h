#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include "States.h"

namespace WI //WI namespace (Window Interface)
{
	
	class Application
	{
	public:
		void Run();
		virtual ~Application();
	
	protected: // For Functions
	
		//Default constructor
		Application();
	
		// Constructor that is called explicitly
		explicit Application(const sf::Vector2u& resolution, const std::string& appName, const sf::Color& clearColor = sf::Color::Black);
		//Deleting the copy constructor
		Application(const Application&) = delete;
		// Getting the Screen Values
		uint32_t GetScreenWidth();
		uint32_t GetScreenHeight();
		virtual void HandleEvents();
		void HandleEvents_();
		virtual void Update();
		virtual void Draw();
		virtual void CheckStates();
		void CheckOGStates();
		static void SetClearColor(const sf::Color& clearColor);
	
	protected: // For variables
		sf::RenderWindow* m_appWindow;
		sf::Event* m_event;
		sf::View m_defaultView;
		static float m_fDTime;
		static sf::Clock m_appClock;
		static States m_eAppState;
	
	private:
		static sf::Color m_clearColor;
	};
}
