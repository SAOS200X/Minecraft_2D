#include "pch.h"
#include "NewWorldState.h"
#include "systemHandle.h"

NewWorldState::NewWorldState()
{
	this->initBackground(m_path::bg_newworld);
	initTextBoxs();
}

NewWorldState::~NewWorldState()
{
	for (auto& i : textBoxs)
		delete i.second;
}

void NewWorldState::update()
{
	for (auto& i : textBoxs)
	{
		i.second->update(static_cast<sf::Vector2f>(systemHandle::getMousePosWindow()), systemHandle::isButtonPressed(sf::Mouse::Left));
		if (systemHandle::getUTFCode())
			i.second->typed(systemHandle::getUTFCode());
	}
}

void NewWorldState::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
	for (auto& i : textBoxs)
		i.second->render(target);
}

void NewWorldState::initTextBoxs()
{
	textBoxs.insert({ "NAME", new TextBox(sf::Vector2f(400.f, 40.f), sf::Vector2f(systemHandle::getWindow()->getSize().x / 2.f, systemHandle::getWindow()->getSize().y * 2.f / 7.f),
		sf::Color::Black, systemHandle::getFont(), 24) });

	textBoxs.insert({ "SEED", new TextBox(sf::Vector2f(150.f, 40.f), sf::Vector2f(systemHandle::getWindow()->getSize().x / 2.f, systemHandle::getWindow()->getSize().y * 4.f / 7.f),
		sf::Color::Black, systemHandle::getFont(), 24) });
}
