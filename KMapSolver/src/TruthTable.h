#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "SFML/Graphics.hpp"
#include "Button.h"

namespace KM
{
	class TruthTable : public sf::Drawable
	{
	public:
		TruthTable(const uint32_t& numberOfVariables, sf::Font* font, sf::RenderWindow* window);
		bool HandleEvents(sf::Event* event);
		void PrintStates();
		void ReConfig();
		std::vector<uint16_t>& GetStatesVector();
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
