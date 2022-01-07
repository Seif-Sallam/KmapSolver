#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "SFML/Graphics.hpp"
#include "Engine/Button.h"

namespace KM
{
	class TruthTable : public sf::Drawable
	{
	public:
		//Constructor to get the important values
		TruthTable(const uint32_t& numberOfVariables, sf::Font* font, sf::RenderWindow* window);
		
		//A function to handle the events of the buttons to know when they are clicked
		bool HandleEvents(sf::Event* event);

		//A function for debugging 
		void PrintStates();

		//Reconfig function to reconfigure the buttons texts when they are clicked on the kmap and not on the table
		void ReConfig();

		//A function to return a reference to the states vector
		//Arguably enough, the states vector should not be originally made here in this class
		//However, this was done just for the convenience of the code and nothing more
		std::vector<uint16_t>& GetStatesVector();

		//Draw function to draw the full table on a single function call
		void draw(sf::RenderTarget& target, sf::RenderStates state = sf::RenderStates::Default) const override;
		~TruthTable();
	private:
		uint32_t m_variablesNum;
		uint32_t m_iRows;
		uint32_t m_iCols;
		sf::RectangleShape* m_cellShapes;
		sf::Text* m_cellsText;
		WI::Button** m_buttons;
		WI::ButtonConfig m_buttonConfig;
		std::vector<uint16_t> m_cellsStates;
		uint32_t m_iSize;
	};
	
}
