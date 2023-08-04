#include "pch.h"
#include "MainMenuState.h"

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
}

void MainMenuState::updateButton()
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
		logWARNING("Couldn't open file: " + filePath);

	backGround.setTexture(*texture);
}

void MainMenuState::initButton()
{
	buttons.push_back(new Button(sf::Vector2u(100,50),sf::Vector2f(200.f,200.f),sf::Color()))
}
