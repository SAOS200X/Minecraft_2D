#include "pch.h"
#include "MainMenuState.h"
#include "GameState.h"
#include "SettingState.h"

MainMenuState::MainMenuState()
{
	initTexture("resource/image/bg.jpg");
	initButton();
}

MainMenuState::~MainMenuState()
{
	delete this->texture;
	for (auto& i : buttons)
		delete i.second;
}

void MainMenuState::update()
{
	for (auto& i : buttons)
		i.second->update(static_cast<sf::Vector2f>(s_System::getMousePosWindow()));

	updateButtonActive();
}

void MainMenuState::updateButtonActive()
{
	for (auto& i : buttons)
	{
		if (i.second->isActive())
		{
			if (i.first == "START")
				State::states->push(new GameState());
			else if (i.first == "OPTION")
				State::states->push(new SettingState());
			else if (i.first == "QUIT")
				State::states->pop();
		}
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
	
	for (auto& i : buttons)
		i.second->render(target);
}

void MainMenuState::initTexture(std::string filePath)
{
	this->texture = new sf::Texture;
	if (!this->texture->loadFromFile(filePath))
		logWARNING("Couldn't open file: " + filePath);

	this->sprite.setTexture(*this->texture);
}

void MainMenuState::initButton()
{
	buttons.insert({"START", new Button("resource/image/singerplayer.png", sf::Vector2f(s_System::getWindow()->getSize().x / 2.f, 300.f))});
	buttons.insert({ "OPTION", new Button("resource/image/option.png", sf::Vector2f(s_System::getWindow()->getSize().x / 2.f - 128.f, 380.f)) });
	buttons.insert({ "QUIT", new Button("resource/image/quit.png", sf::Vector2f(s_System::getWindow()->getSize().x / 2.f + 128.f, 380.f)) });


}
