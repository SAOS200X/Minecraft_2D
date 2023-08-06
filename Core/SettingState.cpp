#include "pch.h"
#include "SettingState.h"

SettingState::SettingState()
{
	initTexture("resource/image/dirt.jpg");
	initDropBoxs("resource/init/setting.init");
}

SettingState::~SettingState()
{
	for (auto& i : settings)
		delete i.second;

	for (auto& i : buttons)
		delete i.second;
}

void SettingState::update()
{
	for (auto& i : settings)
		i.second->update(static_cast<sf::Vector2f>(s_System::getMousePosWindow()),*s_System::getDeltaTime());

	for (auto& i : buttons)
		i.second->update(static_cast<sf::Vector2f>(s_System::getMousePosWindow()));

	updateButtonActive();
}

void SettingState::updateButtonActive()
{
	for (auto& i : buttons)
		if (i.second->isActive())
		{
			if (i.first == "APPLY")
			{
				applySetting();
			}
		}
}

void SettingState::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
	for (auto& i : settings)
		i.second->render(target);

	for (auto& i : buttons)
		i.second->render(target);
}

void SettingState::initTexture(std::string filePath)
{
	this->texture = new sf::Texture;
	if (!this->texture->loadFromFile(filePath))
		logWARNING("Couldn't open file: " + filePath);

	this->sprite.setTexture(*this->texture);
	this->sprite.scale(1.5, 1.5);
}

void SettingState::initButton()
{
	buttons.insert({ "APPLY", new Button(sf::Vector2u(150,50),sf::Vector2f(s_System().getWindow()->getSize().x * 2.f / 3.f, s_System().getWindow()->getSize().y * 4.f / 5.f),
		sf::Color(100,100,255), s_System::getFont(),20, "APPLY") });
}

void SettingState::initDropBoxs(std::string filePath)
{
	std::ifstream INFILE(filePath);
	std::string str;
	if (INFILE.is_open())
	{
		while (INFILE.good())
		{
			std::getline(INFILE, str);

			int off = 0;
			int mark = str.find('(', off);

			std::vector<std::string> v_token;
			std::string tokens = str.substr(mark + 1, str.rfind('(', 0) - 1);

			v_token.push_back(str.substr(off, mark));
			while ((off = tokens.find('{', off)) != std::string::npos)
			{
				v_token.push_back(tokens.substr(off + 1, (mark = tokens.find('}', off)) - (off + 1)));
				off = mark;
			}

			if (v_token.front() == "RESOLUTION")
				addDropBox(sf::Vector2f(200.f, 40.f), sf::Vector2f(200.f, 200.f), v_token, 3);
			else if (v_token.front() == "FPS")
				addDropBox(sf::Vector2f(200.f, 40.f), sf::Vector2f(600.f, 200.f), v_token, 1);
		}
	}
	else
		logWARNING("couldn't open file: " + filePath);
	INFILE.close();
}


void SettingState::addDropBox(sf::Vector2f size, sf::Vector2f position, std::vector<std::string>& tokens, unsigned short current)
{
	settings.insert({ tokens.at(0), new DropDownBox(size,position,sf::Color(100,100,150),s_System::getFont(),18,5) });
	for (size_t i = 1; i < tokens.size(); i++)
		settings[tokens.at(0)]->push(tokens.at(i));

	settings[tokens.at(0)]->setCurrent(current);
}

void SettingState::applySetting()
{
}
