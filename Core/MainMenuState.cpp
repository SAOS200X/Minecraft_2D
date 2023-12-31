#include "pch.h"
#include "MainMenuState.h"
#include "SinglePlayerState.h"
#include "SettingState.h"
#include "systemHandle.h"

MainMenuState::MainMenuState()
{
	this->initBackground(m_path::bg_main);
	initButton();
}

MainMenuState::~MainMenuState()
{
	for (auto& i : buttons)
		delete i.second;
}

void MainMenuState::update()
{
	for (auto& i : buttons)
		i.second->update(static_cast<sf::Vector2f>(systemHandle::getMousePosWindow()), systemHandle::isButtonPressed(sf::Mouse::Left));

	updateButtonActive();
}

void MainMenuState::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
	
	for (auto& i : buttons)
		i.second->render(target);
}

void MainMenuState::reinit()
{
	float scale = systemHandle::getWindow()->getSize().y / static_cast<float>(this->sprite.getLocalBounds().getSize().y);
	this->sprite.setScale(scale, scale);

	buttons.at("START")->setPosition(sf::Vector2f(systemHandle::getWindow()->getSize().x / 2.f, systemHandle::getWindow()->getSize().y / 2.f - 80.f));
	buttons.at("OPTION")->setPosition(sf::Vector2f(systemHandle::getWindow()->getSize().x / 2.f - 128.f, systemHandle::getWindow()->getSize().y / 2.f));
	buttons.at("QUIT")->setPosition(sf::Vector2f(systemHandle::getWindow()->getSize().x / 2.f + 128.f, systemHandle::getWindow()->getSize().y / 2.f));
}

void MainMenuState::initButton()
{
	_MY_DEBUG_

	buttons.insert({"START", new Button(systemHandle::getTexture(m_path::button_singleplayer), 
		sf::Vector2f(systemHandle::getWindow()->getSize().x / 2.f, systemHandle::getWindow()->getSize().y / 2.f - 80.f))});
	buttons.insert({ "OPTION", new Button(systemHandle::getTexture(m_path::button_option), 
		sf::Vector2f(systemHandle::getWindow()->getSize().x / 2.f - 130.f, systemHandle::getWindow()->getSize().y / 2.f)) });
	buttons.insert({ "QUIT", new Button(systemHandle::getTexture(m_path::button_quit), 
		sf::Vector2f(systemHandle::getWindow()->getSize().x / 2.f + 130.f, systemHandle::getWindow()->getSize().y / 2.f)) });
}




void MainMenuState::updateButtonActive()
{
	for (auto& i : buttons)
	{
		if (i.second->isButtonPressed())
		{
			if (i.first == "START")
				State::states->push(new SinglePlayerState());
			else if (i.first == "OPTION")
				State::states->push(new SettingState());
			else if (i.first == "QUIT") {
				State::states->pop();
				delete this;
			}
			return;
		}
	}
}