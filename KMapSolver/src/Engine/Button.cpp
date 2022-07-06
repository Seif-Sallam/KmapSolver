#include "Engine/Button.h"
#include <SFML/System.hpp>
using namespace WI;

Button::Button(sf::RenderWindow *window, ButtonConfig config)
	: m_window(window)
{
	this->config = config;
	AddConfig(config);
	m_text.setCharacterSize(16u);
	sf::FloatRect bounds = m_text.getLocalBounds();
	m_body.setSize(sf::Vector2f(bounds.width + 15.0f, bounds.height + 15.0f));
	m_size = m_body.getSize();
	m_bHasStaticSize = false;
}

bool Button::EventHandling(sf::Event *event, const std::string &newText, bool reAdjust, void (*function)(Button *))
{
	if (MouseOnButton())
		if (event->type == sf::Event::MouseButtonPressed && event->mouseButton.button == sf::Mouse::Left)
		{
			Flicker(true);
			function(this);
			if (newText != "")
				UpdateText(newText, reAdjust);
			return true;
		}
		else
			Flicker(false);
	return false;
}

void Button::UpdateText(const std::string &text, bool reAdjust)
{
	m_text.setString(text);
	m_IsOne = (text == "1");
	if (reAdjust)
	{
		sf::FloatRect bounds = m_text.getLocalBounds();
		m_body.setSize(sf::Vector2f(bounds.width + 15.0f, bounds.height + 25.0f));
		m_size = m_body.getSize();
	}
}

std::string Button::GetButtonText()
{
	return "Text";
}

void Button::SetTextSize(const unsigned int &size)
{
	m_text.setCharacterSize(size);
}

void Button::SetStaticSize(const sf::Vector2f &size)
{
	m_bHasStaticSize = true;
	m_body.setSize(size);
	m_size = size;
	float textWidth = m_text.getLocalBounds().width;
	float textHeight = m_text.getLocalBounds().height;

	m_text.setPosition(m_position.x + textWidth / 4.0f, m_position.y + size.y / 2.0f - textHeight / 2.0f);
	m_position = m_body.getPosition();
}

void Button::SetFont(const sf::Font &font)
{
	m_text.setFont(font);
}

void Button::SetPosition(const sf::Vector2f &position)
{
	m_position = position;
	m_body.setPosition(position.x, position.y + 2.0f);
	if (!m_bHasStaticSize)
		m_text.setPosition(position.x + 5.0f, position.y + 5.0f);
	else
	{
		float textWidth = m_text.getLocalBounds().width;
		float textHeight = m_text.getLocalBounds().height;
		m_text.setPosition(m_position.x + textWidth / 4.0f, m_position.y + m_body.getSize().y / 2.0f - textHeight / 2.0f);
	}
}

sf::Vector2f Button::GetSize() const
{
	return m_body.getSize();
}

void Button::WrapToTopLeftCorner(int index)
{
	sf::Vector2f size = sf::Vector2f(m_window->getView().getSize().x, m_window->getView().getSize().y);
	sf::Vector2f pos = sf::Vector2f(m_window->getView().getCenter().x - size.x / 2.0f, m_window->getView().getCenter().y - size.y / 2.0f);

	SetPosition(sf::Vector2f(pos.x + (m_body.getSize().x + 10.0f) * index, pos.y));
}

void Button::AddConfig(const ButtonConfig &config)
{
	if (config.transparent)
		m_body.setFillColor(sf::Color::Transparent);
	else
		m_body.setFillColor(config.bgColor);
	if (config.hasBorders)
	{
		m_body.setOutlineThickness(config.brdrSize);
		m_body.setOutlineColor(config.brdrColor);
	}
	else
		m_body.setOutlineThickness(0.f);

	if (config.font != nullptr)
	{
		m_text.setFont(*config.font);
	}
	m_text.setFillColor(config.txtColor);
	m_text.setString(config.text);
}

void Button::draw(sf::RenderTarget &window, sf::RenderStates state) const
{
	window.draw(m_body, state);
	window.draw(m_text, state);
}

bool Button::MouseOnButton()
{
	sf::Vector2f mousePos = m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window));

	if (mousePos.x < m_position.x + m_size.x && mousePos.x > m_position.x && mousePos.y < m_position.y + m_size.y && mousePos.y > m_position.y)
		return true;
	return false;
}

void Button::Flicker(bool flickIn)
{
	if (flickIn)
		m_body.setFillColor(config.flickerColor);
	else
		m_body.setFillColor(config.bgColor);
}