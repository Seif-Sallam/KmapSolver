#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>

namespace WI // WI namespace (Window Interface)
{
	
	// Button Config struct to change the config of the button class
	struct ButtonConfig
	{
		bool hasBorders = true, transparent = false;
		sf::Color bgColor = sf::Color::White, txtColor = sf::Color::Black, brdrColor = sf::Color(125, 125, 125), flickerColor = sf::Color(64, 64, 64);
		float brdrSize = 3.0f;
		sf::Font* font = nullptr;
		std::string text = "";
	
		// Default constructor to make things quick
		inline ButtonConfig() {}
	
		// A constructor made for the most popular functions marked inline to prevent writing it in a different file
		inline ButtonConfig(sf::Font* f, const std::string& t)
			: font(f), text(t)
		{}
	};
	
	
	class Button : public sf::Drawable // Inheriting from sf::Drawable to be able to draw it on the screen easily
	{
	public:
		// Constructor takes in a pointer to the window that it will work on and the Config of the button
		Button(sf::RenderWindow* window, ButtonConfig config);
	
		// Adding the configuration to the button
		void AddConfig(const ButtonConfig& config);
	
		// The most important function in the Button where it will check if the mouse clicked on it or not
		// If yes, it will execute the function in it that needs a pointer to the button.
		// I have made changing the text an optional idea because sometimes you would need to change the text without using a function or 
		// knowing the text of the button
		bool EventHandling(sf::Event* event, const std::string& newText = "", bool reAdjust = false, void(*function)(Button*) = [](Button*) {});
	
		// Updating the text of the button and it takes a boolean value "reAdjust" it readjusts the size of the button depending on the Button text
		void UpdateText(const std::string& text, bool reAdjust = false);
	
	
		//A bunch of setters and getters
	
		std::string GetButtonText();
	
		void SetTextSize(const unsigned int& size);
	
		void SetStaticSize(const sf::Vector2f& size);
	
		void SetFont(const sf::Font& font);
	
		void SetPosition(const sf::Vector2f& position);
	
		sf::Vector2f GetSize() const;
	
		// A function made specifically to wrap the button onto the top left corner, more functions to wrap the buttons around a boundary would be added in the future
		// The index identifies which button it is, if it is in a list.
		void WrapToTopLeftCorner(int index);
	
		// A draw function to draw the button properly on the screen using window.draw(button);
		void draw(sf::RenderTarget& window, sf::RenderStates state = sf::RenderStates::Default) const override;
	
	private:
		void Flicker(bool flickIn);
		bool MouseOnButton();
	
	private:
		sf::Text m_text;
		sf::RectangleShape m_body;
		sf::Vector2f m_position;
		sf::RenderWindow* m_window;
		sf::Vector2f m_size;
		ButtonConfig config;
		bool m_bHasStaticSize;
	};
}
