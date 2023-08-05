#include "pch.h"
#include "MainMenuState.h"
#include "GameState.h"

MainMenuState::MainMenuState()
{
	initTexture("resource/image/bg.jpg");
	initButton();
}

MainMenuState::~MainMenuState()
{
	delete texture;
}

void MainMenuState::update()
{
	for (auto i : buttons)
		i.second->update(s_System::getMousePosWindow());

	updateButtonActive();
}

void MainMenuState::updateButtonActive()
{
	for (auto i : buttons)
	{
		if (i.second->isActive())
		{
			if (i.first == "START")
				State::states->push(new GameState());
			else if (i.first == "OPTION")
			{

			}
		}
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	target->draw(backGround);
	
	for (auto i : buttons)
		i.second->render(target);
}

void MainMenuState::initTexture(std::string filePath)
{
	texture = new sf::Texture;
	if (!texture->loadFromFile(filePath))
		logWARNING("Couldn't open file: " + filePath);

	backGround.setTexture(*texture);
}

void MainMenuState::initButton()
{
	buttons.insert({"START", new Button("resource/image/singerplayer.png", sf::Vector2f(s_System::getWindow()->getSize().x / 2.f, 300.f))});
}
