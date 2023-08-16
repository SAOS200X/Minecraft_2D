#include "pch.h"
#include "SettingState.h"
#include "systemHandle.h"
#include "settingHandle.h"
#include "MainMenuState.h"

SettingState::SettingState()
{
	this->initBackground(m_path::bg_setting);
	_MY_DEBUG_

	initDropBoxs();
	initButton();
}

SettingState::~SettingState()
{
	for (auto& i : settings)
		delete i.second;

	for (auto& i : buttons)
		delete i.second;
}

void SettingState::update()
{
	for (auto& i : settings)
	{
		if (systemHandle::isKeyPressed(sf::Keyboard::Up))
			i.second->scrollUp();
		else if (systemHandle::isKeyPressed(sf::Keyboard::Down))
			i.second->ScrollDown();
		i.second->update(static_cast<sf::Vector2f>(systemHandle::getMousePosWindow()), systemHandle::isButtonPressed(sf::Mouse::Left));
	}

	for (auto& i : buttons)
		i.second->update(static_cast<sf::Vector2f>(systemHandle::getMousePosWindow()), systemHandle::isButtonPressed(sf::Mouse::Left));

	updateButtonActive();
}

void SettingState::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
	for (auto& i : settings)
		i.second->render(target);

	for (auto& i : buttons)
		i.second->render(target);
}

void SettingState::initButton()
{
	buttons.insert({ "APPLY", new Button(systemHandle::getTexture(m_path::button_blank), sf::Vector2f(systemHandle().getWindow()->getSize().x * 2.f / 3.f, systemHandle().getWindow()->getSize().y * 4.f / 5.f),
		systemHandle::getFont(),22, "APPLY") });
}

void SettingState::initDropBoxs()
{
	sf::Vector2f position = static_cast<sf::Vector2f>(systemHandle::getWindow()->getSize());
	auto& a = settingHandle::m_setting.get("RESOLUTION");
	settings.insert({ a.first(),
		new DropDownBox(systemHandle::getTexture(m_path::button_blank),sf::Vector2f(position.x / 2.f - 200.f, position.y / 3.f),systemHandle::getFont(),22,4) });
	for (auto& i : a.second()->values)
		settings.at(a.first())->push(i.first());
	settings.at(a.first())->setCurrent(a.second()->current);


	auto& b = settingHandle::m_setting.get("FPS");
	settings.insert({ b.first(),
		new DropDownBox(systemHandle::getTexture(m_path::button_blank),sf::Vector2f(position.x / 2.f + 200.f, position.y / 3.f),systemHandle::getFont(),22,4) });
	for (auto& i : b.second()->values)
		settings.at(b.first())->push(i.first());
	settings[b.first()]->setCurrent(b.second()->current);
}




void SettingState::updateButtonActive()
{
	for (auto& i : buttons)
		if (i.second->isButtonPressed())
		{
			if (i.first == "APPLY")
			{
				applySetting();
				return;
			}
		}
}

void SettingState::applySetting()
{
	bool change = false;
	for (auto& i : settings)
		if (settingHandle::m_setting.at(i.first)->current != i.second->getCurrent())
		{
			settingHandle::m_setting.at(i.first)->current = i.second->getCurrent();
			change = true;
		}

	if (change)
	{
		std::ofstream OUTFILE(m_path::path_window);
		if (OUTFILE.is_open())
		{
			OUTFILE << settingHandle::title << "\n" << "RESOLUTION" << " " << settingHandle::m_setting.at("RESOLUTION")->current << "\n"
				<< "FPS" << " " << settingHandle::m_setting.at("FPS")->current;
			OUTFILE.close();
		}
		else
			logWARNING("couldn't save settings at: " + std::string(m_path::path_window));

		sf::Vector2u size = std::get<sf::Vector2u>(settingHandle::getCurrentSetting("RESOLUTION"));
		settingHandle::window->create(sf::VideoMode(size.x, size.y), settingHandle::title, sf::Style::Close | sf::Style::Titlebar);
		settingHandle::window->setFramerateLimit(std::get<unsigned int>(settingHandle::getCurrentSetting("FPS")));

		State::states->pop();
		static_cast<MainMenuState*>(State::states->top())->reinit();
		delete this;
	}
}
