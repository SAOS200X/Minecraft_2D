#include "pch.h"
#include "SinglePlayerState.h"
#include "systemHandle.h"

SinglePlayerState::SinglePlayerState()
{
	initTexture(m_macro::bg_singleplayer);
	initButton();
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

void SinglePlayerState::initTexture(const std::string filePath)
{
	_MY_DEBUG_

		this->texture = new sf::Texture;
	if (!this->texture->loadFromFile(filePath))
		logWARNING("Couldn't open file: " + filePath);
	this->sprite.setTexture(*this->texture);

	float scale = systemHandle::getWindow()->getSize().y / static_cast<float>(this->texture->getSize().y);
	this->sprite.setScale(scale, scale);
}

void SinglePlayerState::initButton()
{
	sf::Vector2f pos = sf::Vector2f(systemHandle::getWindow()->getSize().x / 2.f, systemHandle::getWindow()->getSize().y * 2.f / 3.f);
	buttons.insert({ "NEWGAME",new Button(m_macro::button_blank, sf::Vector2f(systemHandle::getWindow()->getSize().x / 2.f + 200.f, systemHandle::getWindow()->getSize().y * 2.f / 3.f), systemHandle::getFont(), 24, "New Game") });
	buttons.insert({ "RESUME",new Button(m_macro::button_blank, sf::Vector2f(systemHandle::getWindow()->getSize().x / 2.f - 200.f, systemHandle::getWindow()->getSize().y * 2.f / 3.f), systemHandle::getFont(), 24, "Resume") });
}

void SinglePlayerState::updateButtonActive()
{
	for (auto& i : buttons)
		if (i.first == "")
		{

		}
}

void SinglePlayerState::reinit()
{
}
