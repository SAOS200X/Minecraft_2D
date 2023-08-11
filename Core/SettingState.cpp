#include "pch.h"
#include "SettingState.h"
#include "systemHandle.h"
#include "settingHandle.h"

SettingState::SettingState()
{
	initTexture(m_macro::bg_1);
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
		i.second->update(static_cast<sf::Vector2f>(systemHandle::getMousePosWindow()));

	for (auto& i : buttons)
		i.second->update(static_cast<sf::Vector2f>(systemHandle::getMousePosWindow()));

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

void SettingState::initTexture(const std::string filePath)
{
	_MY_DEBUG_

	this->texture = new sf::Texture;
	if (!this->texture->loadFromFile(filePath))
		logWARNING("Couldn't open file: " + filePath);

	this->sprite.setTexture(*this->texture);
	float scale = systemHandle::getWindow()->getSize().y / static_cast<float>(this->texture->getSize().y);
	this->sprite.setScale(scale, scale);
}

void SettingState::initButton()
{
	buttons.insert({ m_macro::name_3, new Button(sf::Vector2u(150,50),sf::Vector2f(systemHandle().getWindow()->getSize().x * 2.f / 3.f, systemHandle().getWindow()->getSize().y * 4.f / 5.f),
		sf::Color(100,100,255), systemHandle::getFont(),20, m_macro::name_3) });
}

void SettingState::initDropBoxs()
{
	sf::Vector2f position = static_cast<sf::Vector2f>(systemHandle::getWindow()->getSize()) / 2.f;

	settings.insert({ settingHandle::m_setting.get(m_macro::name_1).first(),
		new DropDownBox(sf::Vector2f(200.f, 40.f),sf::Vector2f(position.x - 200.f, position.y - 100.f),sf::Color(100,100,150),systemHandle::getFont(),18,5) });
	settings.at(settingHandle::m_setting.get(m_macro::name_1).first())->push(settingHandle::m_setting.get(m_macro::name_1).second()->values.getKeys());
	settings.at(settingHandle::m_setting.get(m_macro::name_1).first())->setCurrent(settingHandle::m_setting.get(m_macro::name_1).second()->current);

	
	settings.insert({ settingHandle::m_setting.get(m_macro::name_2).first(),
		new DropDownBox(sf::Vector2f(200.f, 40.f),sf::Vector2f(position.x + 200.f, position.y - 100.f),sf::Color(100,100,150),systemHandle::getFont(),18,5) });

	//auto k = settingHandle::m_setting.begin().first();
	//auto j = (settingHandle::m_setting.begin() + 0).first();
	settings[settingHandle::m_setting.get(m_macro::name_2).first()]->push(settingHandle::m_setting.get(m_macro::name_2).second()->values.getKeys());
	settings[settingHandle::m_setting.get(m_macro::name_2).first()]->setCurrent(settingHandle::m_setting.get(m_macro::name_2).second()->current);
}

void SettingState::reinit()
{

}


void SettingState::updateButtonActive()
{
	for (auto& i : buttons)
		if (i.second->isActive())
		{
			if (i.first == m_macro::name_3)
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
		std::ofstream OUTFILE(m_macro::init_0);
		if (OUTFILE.is_open())
		{
			OUTFILE << settingHandle::title << "\n" << m_macro::name_1 << " " << settingHandle::m_setting.at(m_macro::name_1)->current << "\n"
				<< m_macro::name_2 << " " << settingHandle::m_setting.at(m_macro::name_2)->current;
			OUTFILE.close();
		}
		else
			logWARNING("couldn't save settings at: " + std::string(m_macro::init_0));

		sf::Vector2u size = std::get<sf::Vector2u>(settingHandle::getCurrentSetting(m_macro::name_1));
		settingHandle::window->create(sf::VideoMode(size.x, size.y), settingHandle::title, sf::Style::Close | sf::Style::Titlebar);
		settingHandle::window->setFramerateLimit(std::get<unsigned int>(settingHandle::getCurrentSetting(m_macro::name_2)));

		State::states->pop();
		State::states->top()->reinit();
		delete this;
	}
}
