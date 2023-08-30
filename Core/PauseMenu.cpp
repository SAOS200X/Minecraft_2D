#include "pch.h"
#include "PauseMenu.h"
#include "systemHandle.h"

PauseMenu::PauseMenu()
{
	show = false;
	save = false;
	initButton();
}

PauseMenu::~PauseMenu()
{
	for (auto& i : buttons)
		delete i.second;
}

void PauseMenu::update()
{
	for (auto& i : buttons)
		i.second->update(static_cast<sf::Vector2f>(systemHandle::getMousePosWindow()), systemHandle::isButtonPressed(sf::Mouse::Left));
	updateButtonActive();
}

void PauseMenu::render(sf::RenderTarget* target)
{
	target->draw(bg);
	for (auto& i : buttons)
		i.second->render(target);
}

void PauseMenu::initBackGround()
{
	bg.setSize(sf::Vector2f(400.f, static_cast<float>(systemHandle::getWindow()->getSize().y)));
	bg.setOrigin(bg.getSize() / 2.f);
	bg.setPosition(static_cast<sf::Vector2f>(systemHandle::getWindow()->getSize() / 2.f));
	bg.setFillColor(sf::Color(50, 50, 50, 50));
	bg.setOutlineThickness(4.f);
}

void PauseMenu::initButton()
{
	buttons.insert({ "SAVE",new Button(systemHandle::getTexture(m_path::button_blank), sf::Vector2f(systemHandle::getWindow()->getSize().x / 2.f, systemHandle::getWindow()->getSize().y * 4.f / 7.f),
		systemHandle::getFont(), 24, "Save") });
}

void PauseMenu::updateButtonActive()
{
	for (auto& i : buttons)
		if (i.second->isButtonPressed())
		{
			if (i.first == "SAVE")
				save = true;
			return;
		}
}
