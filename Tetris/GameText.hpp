#pragma once
#include <string>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <sstream>
#include <iomanip>

class GameText : public sf::Text {
public:
	GameText(std::string text, int fontSize, float x, float y)
	: Text(), m_font() {

		if (!m_font.loadFromFile("arial.ttf"))
		{
			// error...
			//std::cout << "failed to load font" << std::endl;
		}
		static const sf::Color lightGrey(200, 200, 200);
		setFont(m_font);
		setCharacterSize(fontSize);
		setFillColor(lightGrey);
		setPosition(x, y);
		setStringCentered(text);
	}

	void setStringCentered(std::string text) {
		unsigned int originalSize = getString().getSize();
		setString(text);
		if (text.size() > originalSize) {
			sf::FloatRect textRect = getLocalBounds();
			setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		}
	}

	void setNumberCentered(int number) {
		std::stringstream numberStream;
		numberStream << number;
		setStringCentered(numberStream.str());
	}

	void setTimeCentered(int timeInSeconds) {
		const int SECONDS_PER_MINUTE = 60;
		std::stringstream timeStream;
		int minutes = timeInSeconds / SECONDS_PER_MINUTE;
		int seconds = timeInSeconds % SECONDS_PER_MINUTE;
		timeStream << minutes << ":" << std::setfill('0') << std::setw(2) << seconds;
		setStringCentered(timeStream.str());
	}
private:
	sf::Font m_font;
};
