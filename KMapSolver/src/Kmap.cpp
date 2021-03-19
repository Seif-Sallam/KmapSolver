#include "Kmap.h"

KM::Kmap::Kmap(const uint32_t& numberOfVariables, const sf::Vector2f& offsets, std::vector<uint16_t>& cellStates, sf::RenderWindow* window, sf::Font* font)
	: m_cellState(cellStates), numberOfVariables(numberOfVariables)
{
	//Knowing the number of min terms
	uint32_t minTerms = pow(2, numberOfVariables);
	//Updating the member variables
	m_iMinTerms = minTerms;

	// The number Of Variables  * 2 + 2 (the two texts that indicate the variables names and the combinations)
	m_iSize = 2 * numberOfVariables + 2;

	//declaring the correct sizes
	m_cellText = new sf::Text[m_iSize];
	m_buttons = new WI::Button*[minTerms];
	

	//The expressions data
	m_expressions = new std::bitset<2>[m_iSize];

	sf::Vector2f tileSize = { 45.0f, 45.0f };
	
	//Do the config
	m_buttonConfig.bgColor = sf::Color(209, 75, 0);
	m_buttonConfig.brdrColor = sf::Color(0, 136, 209);
	m_buttonConfig.text = "0";
	m_buttonConfig.flickerColor = sf::Color(209, 139, 0);
	m_buttonConfig.font = font;
	m_buttonConfig.hasBorders = true;
	m_buttonConfig.txtColor = sf::Color::Black;
	m_buttonConfig.brdrSize = 1.f;


	// Adding the buttons with the correct dimensions and the correct sizes
	for (uint32_t i = 0; i < minTerms; i++)
	{
		m_buttons[i] = new WI::Button(window, m_buttonConfig);
		m_buttons[i]->SetStaticSize(tileSize - sf::Vector2f(1.0f, 1.f));
		m_buttons[i]->SetTextSize(25u);
	}
	for (uint32_t i = 0; i < m_iSize; i++)
	{
		m_cellText[i].setFont(*font);
		m_cellText[i].setCharacterSize(25u);
	}

	//Switch statement to fill in the variables and the buttons accordingly
	switch (numberOfVariables)
	{
	case 2:
	{

		//Setting the buttons positions
		for (uint32_t i = 0; i < 2; i++) {
			for (uint32_t j = 0; j < 2; j++)
			{
				sf::Vector2f pos = sf::Vector2f(offsets.x + (tileSize.x + 3.0) * i + 4.0f, offsets.y + (tileSize.y + 3.0) * j + 4.0f);
				m_buttons[i * 2 + j]->SetPosition(pos);
			}
		}
		
		//Setting the texts for the cellTexts
		for (uint32_t i = 0; i < 2; i++)
		{
			m_cellText[i].setString(std::to_string(i));
			m_cellText[i].setPosition(offsets.x + tileSize.x * i, offsets.y - tileSize.y);
		}


		for (uint32_t i = 2, k = 0; i < 4; i++, k++)
		{
			m_cellText[i].setString(std::to_string(i - 2));
			m_cellText[i].setPosition(offsets.x - tileSize.x, offsets.y + tileSize.y * k);
		}
		m_cellText[4].setPosition(offsets.x - tileSize.x * 2.0f, offsets.y);
		m_cellText[4].setString("B");
		m_cellText[5].setPosition(offsets.x, offsets.y - tileSize.y * 2.0f);
		m_cellText[5].setString("A");
	}
	break;
	case 3:
	{
		int32_t index = 0;
		uint32_t indcies[] = { 
			0, 2, 6, 4,
			1, 3, 7, 5
		};

		//Setting the positions
		for (uint32_t i = 0; i < 2; i++)
		{
			for (uint32_t j = 0; j < 4; j++)
			{
				m_buttons[indcies[index++]]->SetPosition(sf::Vector2f(offsets.x + (tileSize.x + 3.0) * j + 4.f, offsets.y + (tileSize.y + 3.0) * i + 4.0f));
			}
		}

		m_expressions[0] = 0;
		m_expressions[1] = 1;
		m_expressions[2] = 3;
		m_expressions[3] = 2;

		for (uint32_t i = 0; i < 4; i++)
		{
			m_cellText[i].setString(m_expressions[i].to_string());
			m_cellText[i].setPosition(offsets.x + tileSize.x * i, offsets.y - tileSize.y);
		}

		m_cellText[4].setString("0");
		m_cellText[5].setString("1");
		for (uint32_t i = 4, k = 0; i < 6; i++, k++)
		{
			m_cellText[i].setPosition(offsets.x - tileSize.x, offsets.y + tileSize.y * k);
		}
		m_cellText[6].setPosition(offsets.x - tileSize.x * 2.0f, offsets.y);
		m_cellText[6].setString("C");
		m_cellText[7].setPosition(offsets.x, offsets.y - tileSize.y * 2.0f);
		m_cellText[7].setString("AB");

	}
	break;
	case 4:
	{
		int32_t index = 0;
		uint32_t indcies[] = {
			0,4,12,8,
			1,5,13,9,
			3,7,15,11,
			2,6,14,10
		};

		for (uint32_t i = 0; i < 4; i++)
			for (uint32_t j = 0; j < 4; j++)
				m_buttons[indcies[index++]]->SetPosition(sf::Vector2f(offsets.x + (tileSize.x + 3.0f) * j, offsets.y + (tileSize.y + 3.0f) * i));
	
		m_expressions[0] = 0;
		m_expressions[1] = 1;
		m_expressions[2] = 3;
		m_expressions[3] = 2;

		m_expressions[4] = 0;
		m_expressions[5] = 1;
		m_expressions[6] = 3;
		m_expressions[7] = 2;

		for (uint32_t i = 0; i < 4; i++)
		{
			m_cellText[i].setString(m_expressions[i].to_string());
			m_cellText[i].setPosition(offsets.x + tileSize.x * i, offsets.y - tileSize.y);
		}

		for (uint32_t i = 4, k = 0; i < 8; i++, k++)
		{
			m_cellText[i].setString(m_expressions[i].to_string());
			m_cellText[i].setPosition(offsets.x - tileSize.x, offsets.y + tileSize.y * k);
		}
		m_cellText[8].setPosition(offsets.x - tileSize.x * 2.0f, offsets.y);
		m_cellText[8].setString("CD");
		m_cellText[9].setPosition(offsets.x , offsets.y - tileSize.y * 2.0f);
		m_cellText[9].setString("AB");
	}
	break;
	}
}

bool KM::Kmap::HandleEvent(sf::Event* event)
{
	//Handling the events for every single button
	for (uint32_t i = 0; i < m_iMinTerms; i++)
	{
		if (m_buttons[i]->EventHandling(event, (m_buttons[i]->GetButtonText() == "0") ? "1" : "0"))
		{
			m_cellState[i] = (m_buttons[i]->GetButtonText() == "0") ? 0 : 1;
			return true;
		}
	}
	return false;
}

void KM::Kmap::ReConfig()
{
	//Updating the data for every button
	for (uint32_t i = 0; i < m_iMinTerms; i++)
	{
		m_buttons[i]->UpdateText(std::to_string(m_cellState[i]));
	}
}

std::string KM::Kmap::Simplify()
{
	
	//Check if they are all 1s and if yes you can just say the function is TRUE
	int32_t trueCounter = 0;
	int32_t falseCounter = 0;
	for (uint32_t  i = 0; i < m_cellState.size(); i++)
	{
		auto& state = m_cellState[i];
		if (state == 1)
			trueCounter++;
		else
			falseCounter++;
	}
	if (trueCounter == m_cellState.size())
	{
		//TODO: Say it is True
#ifdef _DEBUG
		std::cout << "True\n";
#endif // _DEBUG
		return "F= True"; // return and get out of the function
	}
	else if (falseCounter == m_cellState.size())
	{
		//TODO: Say it is False
#ifdef _DEBUG
		std::cout << "False\n";
#endif // _DEBUG
		return "F= False";
	}
	
	//vector that will store the min terms as numbers
	std::vector<uint16_t> minTerms; 
	
	//Getting the min terms from the cell states
	for (uint32_t i = 0; i < m_cellState.size(); i++)
		if (m_cellState[i] == 1)
			minTerms.push_back(i);

	int32_t numberOfMinTerms = minTerms.size();

	//Convert to strings using bit sets

	//The struct is just to make it easier for the algorithm to simplify the expressions
	struct mTerm {
		std::string number;
		bool included = false;
	};

	//The vector that will store the min terms throughout the algorithm
	std::vector<mTerm> minTermsInStrings(numberOfMinTerms);
	
	//Switch statement to know which number of bits to use to represent the numbers
	//since we cannot use a variable in a template class
	switch (numberOfVariables)
	{
	case 2:
	{
		for (int32_t i = 0; i < numberOfMinTerms; i++) {
			std::bitset<2> bits = minTerms[i];
			minTermsInStrings[i].number = bits.to_string();
		}
	}
	break;
	case 3:
	{
		for (int32_t i = 0; i < numberOfMinTerms; i++) {
			std::bitset<3> bits = minTerms[i];
			minTermsInStrings[i].number = bits.to_string();
		}
	}
	break;
	case 4:
	{
		for (int32_t i = 0; i < numberOfMinTerms; i++) {
			std::bitset<4> bits = minTerms[i];
			minTermsInStrings[i].number = bits.to_string();
		}	
	}
	break;
	}
	//NOW we have them as strings, we can now do the double checking
	//Double Checking is just the name i gave to this nested for loop, it should check one element to the adjacent ones


	//This is the vector that will contain the final answers
	std::vector<std::string> sweepVec;
#ifdef _DEBUG

	std::cout << "Before the loop:\n";
	for (uint32_t i = 0; i < minTermsInStrings.size(); i++)
	{
		std::cout << minTermsInStrings[i].number << " ";
	}
	std::cout << "\n---------------------------\n";
#endif // _DEBUG

	// The algorithm should go N - 1 number of times to simplify it the most
	for (uint32_t rounds = 0; rounds < numberOfVariables - 1; rounds++) {
		for (uint32_t i = 0; i < minTermsInStrings.size(); i++)
		{
			// A flag to tell you if the min term you are working on right now was used or not
			bool used = false;

			// The inner loop that will check the bits
			for (uint32_t j = 0; j < minTermsInStrings.size(); j++)
			{
				if (minTermsInStrings[i].number != minTermsInStrings[j].number) {
					int32_t index = -1; // the index with the change
					// This function returns true if there is only ONE bit difference, and populates the index with the index of the changed number.
					if (DifferentByOneBit(minTermsInStrings[i].number, minTermsInStrings[j].number, index))
					{

						// We push it back to the sweep vector
						sweepVec.push_back(minTermsInStrings[i].number);
						// We then change the variable's different bit to something that indicates that it is changed here i used the -
						sweepVec.back()[index] = '-';
						// We make sure that we used this variable
						used = true;
						minTermsInStrings[j].included = true; // we mark the other variable as included in one of the min terms
					}
				}
			}
			// If it happens that one of the variables is never used and never included, then it must be an implicant that cannot be combined with anyone
			// So we have to add it to the sweep vector anyway
			if (!minTermsInStrings[i].included && !used)
				sweepVec.push_back(minTermsInStrings[i].number);
		}
		// We clean the strings to be able to use the array next round
		minTermsInStrings.clear();
		// We sort the sweep vector to be able to remove the duplciates using std::unique
		std::sort(sweepVec.begin(), sweepVec.end());

		// Removing the duplicates
		auto it = std::unique(sweepVec.begin(), sweepVec.end());
		sweepVec.resize(std::distance(sweepVec.begin(), it));
		// Here I am populating the vector of strings with the new elements that it should work on
		for (uint32_t i = 0; i < sweepVec.size(); i++)
		{
			mTerm term{ sweepVec[i], false };
			minTermsInStrings.push_back(term);
		}

		// Just for debugging
#ifdef _DEBUG
		std::cout << rounds << std::endl;
		for (uint32_t i = 0; i < sweepVec.size(); i++)
		{
			std::cout << sweepVec[i] << " ";
		}
		std::cout << "\n----------------------\n";
#endif // _DEBUG
		
		//because I want the sweep vector to be cleaned each and every iteration, and i want to also leave it as is in the final one
		if(rounds != numberOfVariables - 2)
			sweepVec.clear();
		
	}	
	//Removing the equivalent terms 
	int smallerVariable = -1;
	for (uint16_t i = 0; i < sweepVec.size(); i++)
		for (uint16_t j = i + 1; j < sweepVec.size(); j++)
			if (IsEquivalent(sweepVec[i], sweepVec[j], smallerVariable))
			{
				int16_t removedIndex = (smallerVariable == 0) ? i : j;
				sweepVec.erase(sweepVec.begin() + removedIndex);
			}

#ifdef _DEBUG
	std::cout << "outside " << std::endl;
	for (uint32_t i = 0; i < sweepVec.size(); i++)
	{
		std::cout << sweepVec[i] << " ";
	}
	std::cout << "\n----------------------\n";
#endif // _DEBUG
	//Converting the output to simplified expression
	std::string result = "F= ";
	for (uint32_t i = 0; i < sweepVec.size(); i++)
	{
		for (uint32_t j = 0; j < numberOfVariables; j++)
		{
			char bit = sweepVec[i][j];
			if (bit != '-')
			{
				//This means it is equal to either 0 or 1
				char character = char((int)'A' + (int)j);
				result += character;
				if (bit == '0')
				{
					result += '\'';
				}
			}
		}
		if(i != sweepVec.size() - 1)
			result += " + ";
	}
	return result;
}

void KM::Kmap::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	for (uint32_t i = 0; i < m_iSize; i++)
		target.draw(m_cellText[i]);
	for (uint32_t i = 0; i < m_iMinTerms; i++)
		target.draw(*m_buttons[i]);
}

KM::Kmap::~Kmap()
{
	//Deleting the allocated memory
	for (uint32_t i = 0; i < m_iMinTerms; i++)
		delete m_buttons[i];
	delete[] m_buttons;
	delete[] m_cellText;
	delete[] m_expressions;
}

bool KM::Kmap::IsEquivalent(const std::string& first, const std::string& second, int& deletingString)
{
	//Checking if the two literals are equivalent
	int16_t length = first.length();
	uint16_t differenceCounter = 0;

	//Knowing the number of different bits
	for (uint16_t i = 0; i < length; i++)
		if (first[i] != second[i])
			differenceCounter++;

	//if the number of different bits <= 1 means that they are equivilent
	if (differenceCounter <= 1)
	{
		//Knowing the number of dashes in each literals as the one with the more dashes is the best case
		int16_t firstDashes = 0;
		int16_t secondDashes = 0;
		for (uint16_t i = 0; i < length; i++)
		{
			if (first[i] == '-')
				firstDashes++;
			if (second[i] == '-')
				secondDashes++;
		}
		deletingString = (firstDashes > secondDashes) ? 1 : 0; // Updating the string that should be deleted;
		return true;
	}
	return false;
}

bool KM::Kmap::DifferentByOneBit(const std::string& first, const std::string& second, int& index)
{
	//Knowing if the they are different by one bit or not
	int32_t counter = 0;
	for (uint32_t i = 0; i < first.length(); i++)
	{
		if (first[i] != second[i] && (first[i] != '-' || second[i] != '-')) {
			counter++;
			index = i; // changing to the index of the literal to know where to put the dash
		}	
	}	
	return (counter != 1) ? false : true;
}