#include "pch.h"
#include "MainMenuState.h"
#include "SinglePlayerState.h"
#include "SettingState.h"
#include "systemHandle.h"

MainMenuState::MainMenuState()
{
	initTexture(m_macro::bg_main);
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

void MainMenuState::initTexture(const std::string filePath)
{
	_MY_DEBUG_

	this->texture = new sf::Texture;
	if (!this->texture->loadFromFile(filePath))
		logWARNING("Couldn't open file: " + filePath);
	this->sprite.setTexture(*this->texture);

	float scale = systemHandle::getWindow()->getSize().y / static_cast<float>(this->texture->getSize().y);
	this->sprite.setScale(scale, scale);
}

void MainMenuState::initButton()
{
	_MY_DEBUG_

	buttons.insert({"START", new Button(m_macro::button_singleplayer, sf::Vector2f(systemHandle::getWindow()->getSize().x / 2.f, 300.f))});
	buttons.insert({ "OPTION", new Button(m_macro::button_option, sf::Vector2f(systemHandle::getWindow()->getSize().x / 2.f - 128.f, 380.f)) });
	buttons.insert({ "QUIT", new Button(m_macro::button_quit, sf::Vector2f(systemHandle::getWindow()->getSize().x / 2.f + 128.f, 380.f)) });
}

void MainMenuState::reinit()
{
	float scale = systemHandle::getWindow()->getSize().y / static_cast<float>(this->texture->getSize().y);
	this->sprite.setScale(scale, scale);

	buttons.at("START")->setPosition(sf::Vector2f(systemHandle::getWindow()->getSize().x / 2.f, systemHandle::getWindow()->getSize().y / 2.f));
	buttons.at("OPTION")->setPosition(sf::Vector2f(systemHandle::getWindow()->getSize().x / 2.f - 128.f, systemHandle::getWindow()->getSize().y / 2.f + 80.f));
	buttons.at("QUIT")->setPosition(sf::Vector2f(systemHandle::getWindow()->getSize().x / 2.f +128.f, systemHandle::getWindow()->getSize().y / 2.f + 80.f));
}



void MainMenuState::updateButtonActive()
{
	for (auto& i : buttons)
	{
		if (i.second->isActive())
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