#include <fstream>
#include "Button.h"
#include "Application.h"
#include "MapsManager.h"

namespace KM {
	//enum to show the number of variables
	enum class KmapState {
		TwoVar,
		ThreeVar,
		FourVar
	};

	//Inheriting from the Application class that manages all the window and interface
	class KMapSolver : public WI::Application
	{

	public:
		//Constructor to initialize the variables
		KMapSolver()
			: numberOfVariables(3)
		{
			//Setting the screen color
			SetClearColor(sf::Color(0, 47, 128));

			//Loading the font 
			font.loadFromFile("OpenSans-Semibold.ttf");

			//Setting the text font
			simplificationText.setFont(font);

			//Initializing the essential variables
			table = new TruthTable(numberOfVariables, &font, m_appWindow);
			kmap = new Kmap(numberOfVariables, sf::Vector2f(400.0f, 300.0f), table->GetStatesVector(), m_appWindow, &font);
			mm = new MapsManager(*table, *kmap);

			//Setting some other variable
			backgroundTexture.loadFromFile("background.png");
			background.setTexture(backgroundTexture);
			background.setScale(0.7, 0.7);

			simplificationText.setString("F = ");
			simplificationText.setPosition(sf::Vector2f(100.0f, 800.0f));
			simplificationText.setCharacterSize(40u);

			//Button Config and how it looks like
			WI::ButtonConfig config;
			config.bgColor = sf::Color(207, 208, 209);
			config.brdrColor = sf::Color(12, 12, 12);
			config.text = "0";
			config.flickerColor = sf::Color(64, 64, 64);
			config.font = &font;
			config.hasBorders = true;
			config.txtColor = sf::Color(21, 114, 122);
			config.brdrSize = 5.f;
			
			//Setting the switch buttons positions and initializing them
			for (uint16_t i = 0; i < 3; i++) {
				switchButtons[i] = new WI::Button(m_appWindow, config);
				switchButtons[i]->SetPosition(sf::Vector2f(700.0f, 150.0f + 150 * i));
				switchButtons[i]->SetTextSize(30u);
				switchButtons[i]->UpdateText(std::string(std::to_string(2 + i) + " Variables"), true);
			}

			//The save button
			saveButton = new WI::Button(m_appWindow, config);
			saveButton->SetTextSize(40u);
			saveButton->UpdateText("Save!", true);
			saveButton->SetPosition(sf::Vector2f(730.0f, 600.0f));
		}
		
		//Adding the events
		void HandleEvents() override
		{

			if (switchButtons[0]->EventHandling(m_event))
			{
				// Making sure it is NOT the current state
				if (kmapState != KmapState::TwoVar) {
					//Redeclaring the variables
					delete table;
					delete mm;
					delete kmap;
					numberOfVariables = 2;
					table = new TruthTable(numberOfVariables, &font, m_appWindow);
					kmap = new Kmap(numberOfVariables, sf::Vector2f(400.0f, 300.0f), table->GetStatesVector(), m_appWindow, &font);
					mm = new MapsManager(*table, *kmap);
					kmapState = KmapState::TwoVar;
					simplificationText.setString("F = ");
					simplifiedText = "False";
				}
			}
			if (switchButtons[1]->EventHandling(m_event))
			{
				if (kmapState != KmapState::ThreeVar) {
					delete table;
					delete mm;
					delete kmap;
					numberOfVariables = 3;
					table = new TruthTable(numberOfVariables, &font, m_appWindow);
					kmap = new Kmap(numberOfVariables, sf::Vector2f(400.0f, 300.0f), table->GetStatesVector(), m_appWindow, &font);
					mm = new MapsManager(*table, *kmap);
					kmapState = KmapState::ThreeVar;
					simplificationText.setString("F = ");
					simplifiedText = "False";
				}
			}
			if (switchButtons[2]->EventHandling(m_event))
			{
				if (kmapState != KmapState::FourVar) {
					delete table;
					delete mm;
					delete kmap;
					numberOfVariables = 4;
					table = new TruthTable(numberOfVariables, &font, m_appWindow);
					kmap = new Kmap(numberOfVariables, sf::Vector2f(400.0f, 300.0f), table->GetStatesVector(), m_appWindow, &font);
					mm = new MapsManager(*table, *kmap);
					kmapState = KmapState::FourVar;
					simplificationText.setString("F = ");
					simplifiedText = "False";
				}
			}
			if (table->HandleEvents(m_event))
			{
				//Update the other map and find the simplified expression
				mm->UpdateInTheOther(1);
				simplifiedText = kmap->Simplify();
				simplificationText.setString(simplifiedText);
			}
			if (kmap->HandleEvent(m_event))
			{
				//Update the other table and find the simplified expression
				mm->UpdateInTheOther(0);
				simplifiedText = kmap->Simplify();
				simplificationText.setString(simplifiedText);
			}
			if (saveButton->EventHandling(m_event))
			{
				//Saving the data in the file
				std::ofstream outputFile;
				std::ifstream outFileNumber;
				//Knowing how many files are there already existing
				outFileNumber.open("numberOfFiles.dat");
				int32_t numberOfFiles = 1;

				if (outFileNumber.fail())
				{
#ifdef _DEBUG
					std::cout << "output number of File was not opened\n";
					std::cout << "Creating a new file!\n";
#endif // _DEBUG
				}
				else
				{
					if (outFileNumber.eof()) {
						numberOfFiles = 1;
					}
					else
					{
						std::string temp;
						std::getline(outFileNumber, temp);
						numberOfFiles = stoi(temp);
					}
				}

				//The output file name
				std::string output = "Kmap" + std::to_string(numberOfFiles) + ".txt";

				outFileNumber.close();

				//Updating the number of files
				outputFile.open("numberOfFiles.dat");
				outputFile << ++numberOfFiles;
				outputFile.close();

				bool uniqueFile = false;
				//Now we have a unique file opened
				while (!uniqueFile)
				{
					outputFile.open(output);
					if (!outputFile.good())
						uniqueFile = true;
					else
					{
						outputFile.close();
						numberOfFiles++;
						output = "Kmap" + std::to_string(numberOfFiles) + ".txt";
					}
				}
				outputFile.open(output);

				//Starting to output the data to the file
				auto& statsVec = table->GetStatesVector();
				outputFile << "This is a representation of the Kmap that is " << numberOfVariables << "x" << ((numberOfVariables == 3) ? 2 : numberOfVariables) << ":\n";
				outputFile << "This is the Kmap: \n";
				std::vector<uint16_t> indiciesVec;
				uint16_t rows;
				uint16_t cols;
				//To know the dimensions of the kmap
				//The indiciesVector is the one that shows which one to output
				switch (numberOfVariables)
				{
				case 2:
					indiciesVec = { 0, 2, 1, 3 };
					rows = 2;
					cols = 2;
					outputFile << "      A\n";
					outputFile << "B  ";
					break;
				case 3:
					outputFile << "      AB\n";
					outputFile << "C  ";
					indiciesVec = { 0, 2, 6, 4, 1, 3, 7, 5 };
					rows = 2;
					cols = 4;
					break;
				case 4:
					outputFile << "       AB\n";
					outputFile << "CD ";
					indiciesVec = { 0, 4, 12, 8, 1, 5, 13, 9,3, 7, 15, 11, 2, 6, 14, 10 };
					rows = 4;
					cols = 4;
					break;
				default:
#ifdef _DEBUG
					std::cout << "Couldn't save the file";
#endif // _DEBUG
					outputFile.close();
					return;
					break;
				}

				// Printing the kmap itself
				for (uint16_t i = 0; i < rows; i++)
				{
					if (i != 0)
					{
						outputFile << "   ";
					}
					for (uint16_t j = 0; j < cols; j++)
					{
						uint16_t index = i * cols + j;
						outputFile << statsVec[indiciesVec[index]] << " ";
					}
					outputFile << std::endl;
				}

				//Printing the simplified expression
				outputFile << "The simplified expression is: " << std::endl;
				outputFile << simplifiedText;
				outputFile.close();
			}

		}
		void Update() override {
		}
		void Draw() override {
			//Drawing the data one by one
			m_appWindow->draw(background);
			m_appWindow->draw(simplificationText);
			m_appWindow->draw(*table);
			m_appWindow->draw(*kmap);
			m_appWindow->draw(*saveButton);
			for (uint16_t i = 0; i < 3; i++)
				m_appWindow->draw(*switchButtons[i]);
		}

	private:
		sf::Sprite background;
		sf::Texture backgroundTexture;
		TruthTable* table;
		sf::Font font;
		Kmap* kmap;
		MapsManager* mm;
		uint32_t numberOfVariables;
		sf::Text simplificationText;
		WI::Button* switchButtons[3];
		KmapState kmapState = KmapState::ThreeVar;
		WI::Button* saveButton;
		std::string simplifiedText = "False";
	};
}

int main()
{
	KM::KMapSolver e;
	e.Run();
	return 0;
}