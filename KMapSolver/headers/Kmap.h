#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Engine/Button.h"
#include <iterator>
#include <algorithm>
#include <bitset>

namespace KM {
	//The struct is just to make it easier for the algorithm to simplify the expressions
	struct mTerm {
		std::string number;
		bool included = false;
		std::vector<int> coveredTerms;
		mTerm()
		{
			number = "";
		}
		mTerm(const mTerm& other)
		{
			this->number = other.number;
			this->included = other.included;
			for (int i = 0; i < other.coveredTerms.size(); i++)
			{
				this->coveredTerms.push_back(other.coveredTerms[i]);
			}
		}
		//Those operators are there for std::sort and std::unique
		bool operator==(const mTerm& other)
		{
			return this->number == other.number;
		}
		bool operator>=(const mTerm& other)
		{
			return this->number >= other.number;
		}
		bool operator<=(const mTerm& other)
		{
			return this->number <= other.number;
		}
		bool operator<(const mTerm& other)
		{
			return this->number < other.number;
		}
		bool operator>(const mTerm& other)
		{
			return this->number > other.number;
		}
	};
	//Inheriting from sf::Drawable to be able to draw directly using sf::RenderWindow::draw();
	class Kmap : public sf::Drawable
	{
	public:
		//Constructor to pass in the needed variables
		Kmap(const uint32_t& numberOfVariables, const sf::Vector2f& offsets,
			std::vector<uint16_t>& cellStates, sf::RenderWindow* window, sf::Font* font);
		//Handle the events
		bool HandleEvent(sf::Event* event);
		//Updating the texts of the buttons
		void ReConfig();
		//Returning the simplified version of the kmap
		std::string Simplify();

		//overriding the draw function to draw the kmap directly
		void draw(sf::RenderTarget& target, sf::RenderStates state = sf::RenderStates::Default) const override;
		~Kmap();
	private:
		//To know if two literals are equivalent or not
		bool IsEquivalent(const std::string& first, const std::string& second, int32_t& smallerString);

		//A generic Binray to decimal converter function
		uint32_t BtoD(uint32_t term);

		//A helper function to get Terms in variables 
		std::string TermInVariables(const std::string& term);
		//To know if two literals are different by one bit
		bool DifferentByOneBit(const std::string& first, const std::string& second, int32_t& index);
		std::vector<uint16_t>& m_cellState;
		sf::Text* m_cellText;
		WI::Button** m_buttons;
		uint32_t m_iMinTerms;
		uint32_t m_iSize;
		WI::ButtonConfig m_buttonConfig;
		std::bitset<2>* m_expressions;
		const uint32_t numberOfVariables;
		bool usedArray[16]{ false };
	};
}
