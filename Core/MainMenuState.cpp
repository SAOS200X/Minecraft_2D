#include "pch.h"
#include "MainMenuState.h"

MainMenuState::MainMenuState()
{
	initTexture("resource/bg.jpg");
}

MainMenuState::~MainMenuState()
{
	delete texture;
}

void MainMenuState::update()
{
}

void MainMenuState::render(sf::RenderTarget* target)
{
	target->draw(backGround);
}

void MainMenuState::initTexture(std::string filePath)
{
	texture = new sf::Texture;
	if (!texture->loadFromFile(filePath))
		logMSG("Couldn't open file: " + filePath);

	backGround.setTexture(*texture);
}
