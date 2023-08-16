#include "pch.h"
#include "SinglePlayerState.h"
#include "systemHandle.h"
#include "NewWorldState.h"

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
	bool select = false;
	for (auto& i : saves)
	{
		i.update(static_cast<sf::Vector2f>(systemHandle::getMousePosWindow()), systemHandle::isButtonPressed(sf::Mouse::Left));
		if (i.isSelect())
			select = true;
	}

	buttons.at("RESUME")->setActive(select);
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
	buttons.insert({ "NEWGAME",new Button(systemHandle::getTexture(m_path::button_blank), sf::Vector2f(systemHandle::getWindow()->getSize().x / 2.f + 200.f, 
		systemHandle::getWindow()->getSize().y * 6.f / 7.f), systemHandle::getFont(), 24, "New Game") });
	buttons.insert({ "RESUME",new Button(systemHandle::getTexture(m_path::button_blank), sf::Vector2f(systemHandle::getWindow()->getSize().x / 2.f - 200.f, 
		systemHandle::getWindow()->getSize().y * 6.f / 7.f), systemHandle::getFont(), 24, "Resume") });
	buttons.at("RESUME")->setActive(false);
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
			std::string name, savePath, seed;
			time_t date;
			for (unsigned int i = 0; i < num; i++)
			{
				std::getline(INFILE, name);
				std::getline(INFILE, savePath);
				INFILE >> date;
				INFILE.ignore();
				std::getline(INFILE, seed);

				saves.emplace_back(sf::Vector2f(600.f,80.f), sf::Vector2f(systemHandle::getWindow()->getSize().x / 2.f, systemHandle::getWindow()->getSize().y * 2.f / 7.f + 100.f * i),
					systemHandle::getFont());
				saves.back().setPropertite(name, savePath, seed, date);
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
		}
}

