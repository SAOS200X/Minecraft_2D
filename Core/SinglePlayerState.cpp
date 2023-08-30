#include "pch.h"
#include "SinglePlayerState.h"
#include "systemHandle.h"
#include "NewWorldState.h"
#include "GameState.h"

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
	for (auto& i : saves)
	{
		i.update(static_cast<sf::Vector2f>(systemHandle::getMousePosWindow()), systemHandle::isButtonPressed(sf::Mouse::Left));
		if (i.isSelect())
		{
			buttons.at("PLAY")->setActive(true);
			pathIndex = i.getSaves().filePath;
		}
	}
	for (auto& i : buttons)
		i.second->update(static_cast<sf::Vector2f>(systemHandle::getMousePosWindow()), systemHandle::isButtonPressed(sf::Mouse::Left));

	updateButtonActive();
}

void SinglePlayerState::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
	for (auto& i : buttons)
		i.second->render(target);

	for (auto& i : saves)
		i.render(target);
}

void SinglePlayerState::initButton()
{
	buttons.insert({ "NEWGAME",new Button(systemHandle::getTexture(m_path::button_blank), sf::Vector2f(systemHandle::getWindow()->getSize().x / 2.f + 300.f, 
		systemHandle::getWindow()->getSize().y * 6.f / 7.f), systemHandle::getFont(), 24, "Create New World") });
	buttons.insert({ "PLAY",new Button(systemHandle::getTexture(m_path::button_blank), sf::Vector2f(systemHandle::getWindow()->getSize().x / 2.f - 300.f, 
		systemHandle::getWindow()->getSize().y * 6.f / 7.f), systemHandle::getFont(), 24, "Play Selected World") });
	buttons.at("PLAY")->setActive(false);
	buttons.insert({ "CANCEL",new Button(systemHandle::getTexture(m_path::button_blank), sf::Vector2f(systemHandle::getWindow()->getSize().x / 2.f, systemHandle::getWindow()->getSize().y * 6.f / 7.f),
		systemHandle::getFont(), 24, "Cancel") });
}

void SinglePlayerState::loadGlobalSave(const std::string filePath)
{
	unsigned int num = 0;

	std::ifstream INFILE(filePath);
	if (INFILE.is_open())
	{
		INFILE >> num;
		INFILE.ignore();
		if (num)
		{
			std::string name, path, seed;
			time_t date;
			for (unsigned int i = 0; i < num; i++)
			{
				std::getline(INFILE, name);
				std::getline(INFILE, path);
				INFILE >> date;
				INFILE.ignore();
				std::getline(INFILE, seed);

				saves.emplace_back(sf::Vector2f(600.f,80.f), sf::Vector2f(systemHandle::getWindow()->getSize().x / 2.f, systemHandle::getWindow()->getSize().y * 2.f / 7.f + 100.f * i),
					systemHandle::getFont());
				saves.back().setPropertite(name, path, seed, date);
			}
		}
		INFILE.close();
	}
	else
		logERROR("couldn't not load global save: " + filePath);
}

void SinglePlayerState::updateButtonActive()
{
	for (auto& i : buttons)
		if (i.second->isButtonPressed())
		{
			if (i.first == "NEWGAME")
				this->states->push(new NewWorldState());
			else if (i.first == "PLAY")
			{
				this->states->pop();
				this->states->push(new GameState(pathIndex));
				delete this;
			}
			else if (i.first == "CANCEL")
			{
				this->states->pop();
				delete this;
			}
			return;
		}
}

