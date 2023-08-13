#include "pch.h"
#include "SinglePlayerState.h"
#include "systemHandle.h"

SinglePlayerState::SinglePlayerState()
{
	this->initBackground(m_path::bg_singleplayer);
	initButton();
	loadGlobalSave(m_path::save_global);
}

SinglePlayerState::~SinglePlayerState()
{
	for (auto& i : buttons)
		delete i.second;
}

void SinglePlayerState::update()
{
	for (auto& i : buttons)
		i.second->update(static_cast<sf::Vector2f>(systemHandle::getMousePosWindow()), systemHandle::isButtonPressed(sf::Mouse::Left));
}

void SinglePlayerState::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
	for (auto& i : buttons)
		i.second->render(target);
}

void SinglePlayerState::initButton()
{
	buttons.insert({ "NEWGAME",new Button(m_path::button_blank, sf::Vector2f(systemHandle::getWindow()->getSize().x / 2.f + 200.f, systemHandle::getWindow()->getSize().y * 6.f / 7.f), systemHandle::getFont(), 24, "New Game") });
	buttons.insert({ "RESUME",new Button(m_path::button_blank, sf::Vector2f(systemHandle::getWindow()->getSize().x / 2.f - 200.f, systemHandle::getWindow()->getSize().y * 6.f / 7.f), systemHandle::getFont(), 24, "Resume") });
}

void SinglePlayerState::loadGlobalSave(const std::string filePath)
{
	unsigned int num = 0;

	std::ifstream INFILE(filePath);
	if (INFILE.is_open())
	{
		INFILE >> num;
		if (num)
		{

		}
		INFILE.close();
	}
	else
		logERROR("couldn't not load global save: " + filePath);


	if (num > 0)
		saves.push_back(save());
	else
		buttons.at("RESUME")->setActive(false);
}

void SinglePlayerState::updateButtonActive()
{
	for (auto& i : buttons)
		if (i.first == "")
		{

		}
}

