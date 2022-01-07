#include "TruthTable.h"
#include <math.h>
/*
	The whole constructor is used to initialize the values inside the class and to know the positions of the cells
	The way it is used is quite raw bust and hard coded positions were used, however, this was the only way since
	the truth table had many different sections (the variables names, the truth values, the buttons, and each cell's text)
*/
KM::TruthTable::TruthTable(const uint32_t &numberOfVariables, sf::Font *font, sf::RenderWindow *window)
{

	uint32_t minTerms = pow(2, numberOfVariables);

	/*
	Cols:
	The number of variables
	
	Rows:
	2 ^ number Of variables
	+
	1ROW for the variable titles
	CELLS:
	Cols * Rows + 1 (the one is the title of the output)
	
	*/
	m_iRows = minTerms + 1;
	m_iCols = numberOfVariables;
	m_iSize = m_iRows * m_iCols + 1;

	float tileSize = 45.0f;

	/*
	Rows We have the the variables and one title for the variables
	3 columns represent the min terms values for the
	*/
	m_cellsText = new sf::Text[m_iSize];
	m_cellShapes = new sf::RectangleShape[m_iSize];
	m_buttons = new WI::Button *[m_iRows - 1];

	m_buttonConfig.bgColor = sf::Color(209, 75, 0);
	m_buttonConfig.brdrColor = sf::Color::White;
	m_buttonConfig.text = "0";
	m_buttonConfig.flickerColor = sf::Color(209, 139, 0);
	m_buttonConfig.font = font;
	m_buttonConfig.brdrSize = 1.5f;
	m_buttonConfig.hasBorders = true;
	m_buttonConfig.txtColor = sf::Color::Black;

	for (uint32_t i = 0; i < m_iRows - 1; i++)
	{
		m_cellsStates.push_back(0);
	}

	for (uint32_t i = 0; i < m_iRows - 1; i++)
	{
		m_buttons[i] = new WI::Button(window, m_buttonConfig);
		m_buttons[i]->SetStaticSize(sf::Vector2f(tileSize - 2.0f, tileSize - 2.0f));
		m_buttons[i]->SetTextSize(30u);
	}
	for (uint32_t i = 0; i < m_iSize; i++)
	{
		m_cellsText[i].setFont(*font);
		m_cellShapes[i].setSize(sf::Vector2f(tileSize - 2.0f, tileSize - 2.0f));
		m_cellShapes[i].setFillColor(sf::Color(0, 179, 0));
		m_cellShapes[i].setOutlineThickness(1.f);
		m_cellShapes[i].setOutlineColor(sf::Color::White);
	}
	for (uint32_t i = 0; i < numberOfVariables; i++)
	{
		m_cellShapes[i].setFillColor(sf::Color(179, 0, 0));
	}
	m_cellShapes[m_iSize - 1].setFillColor(sf::Color(179, 0, 0));
	// PUtting each and everyone in place

	//putting the buttons
	sf::Vector2f offset;
	offset.x = numberOfVariables * tileSize; // this is for the buttons
	offset.y = 50.0f;						 // a common offset

	for (uint32_t i = 0; i < m_iRows - 1; i++)
	{
		m_buttons[i]->SetPosition(sf::Vector2f(offset.x, offset.y + i * tileSize - 7.0f));
	}
	for (uint32_t i = 0; i < m_iRows; i++)
	{
		for (uint32_t j = 0; j < m_iCols; j++)
		{
			uint32_t index = i * m_iCols + j;
			(m_cellShapes + index)->setPosition(sf::Vector2f(j * tileSize, i * tileSize));
			(m_cellsText + index)->setPosition(sf::Vector2f(j * tileSize + 5.0f, i * tileSize + 5.0f));
		}
	}
	for (uint32_t i = 0; i < numberOfVariables; i++)
	{
		char c = 65 + i;
		(m_cellsText + i)->setString(c);
	}
	m_cellsText[m_iSize - 1].setString("F");
	m_cellsText[m_iSize - 1].setPosition(sf::Vector2f(numberOfVariables * tileSize + 5.0f, 5.0f));
	m_cellShapes[m_iSize - 1].setPosition(sf::Vector2f(numberOfVariables * tileSize, 0.0f));

	for (int32_t i = m_iCols - 1, k = 0; i >= 0; i--, k++)
	{
		uint32_t behavior = pow(2, k);
		uint32_t counter = 1;
		std::string txt = "0";
		for (uint32_t j = 1; j < m_iRows; j++)
		{
			uint32_t index = j * m_iCols + i;
			m_cellsText[index].setString(txt);
			if (counter == behavior)
			{
				txt = (txt == "0") ? "1" : "0";
				counter = 1;
			}
			else
				counter++;
		}
	}
}

bool KM::TruthTable::HandleEvents(sf::Event *event)
{
	for (uint32_t i = 0; i < m_iRows - 1; i++)
	{
		if (m_buttons[i]->EventHandling(event, (!m_buttons[i]->IsOne()) ? "1" : "0"))
		{
			m_cellsStates[i] = (!m_buttons[i]->IsOne()) ? 0 : 1;
			return true;
		}
	}
	return false;
}

void KM::TruthTable::PrintStates()
{
	for (uint32_t i = 0; i < m_cellsStates.size(); i++)
	{
		std::cout << m_cellsStates[i] << " ";
	}
	std::cout << std::endl;
}

void KM::TruthTable::ReConfig()
{
	for (uint32_t i = 0; i < m_iRows - 1; i++)
	{
		m_buttons[i]->UpdateText(std::to_string(m_cellsStates[i]));
	}
}

std::vector<uint16_t> &KM::TruthTable::GetStatesVector()
{
	return m_cellsStates;
}

void KM::TruthTable::draw(sf::RenderTarget &target, sf::RenderStates state) const
{

	for (uint32_t i = 0; i < m_iSize; i++)
	{
		target.draw(m_cellShapes[i]);
		target.draw(m_cellsText[i]);
	}
	for (uint32_t i = 0; i < m_iRows - 1; i++)
		target.draw(*m_buttons[i]);
}

KM::TruthTable::~TruthTable()
{
	for (uint32_t i = 0; i < m_iRows - 1; i++)
	{
		delete m_buttons[i];
	}
	delete[] m_buttons;
	delete[] m_cellsText;
	delete[] m_cellShapes;
	m_cellsStates.clear();
}
