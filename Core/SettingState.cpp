#include "pch.h"
#include "SettingState.h"
#include "systemHandle.h"
#include "settingHandle.h"

SettingState::SettingState()
{
	initTexture("resource/image/bg_menu.png");
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
	buttons.insert({ "APPLY", new Button(sf::Vector2u(150,50),sf::Vector2f(systemHandle().getWindow()->getSize().x * 2.f / 3.f, systemHandle().getWindow()->getSize().y * 4.f / 5.f),
		sf::Color(100,100,255), systemHandle::getFont(),20, "APPLY") });
}

void SettingState::initDropBoxs()
{
	sf::Vector2f position = static_cast<sf::Vector2f>(systemHandle::getWindow()->getSize()) / 2.f;

	settings.insert({ settingHandle::m_setting.get("RESOLUTION").first(),
		new DropDownBox(sf::Vector2f(200.f, 40.f),sf::Vector2f(position.x - 200.f, position.y - 100.f),sf::Color(100,100,150),systemHandle::getFont(),18,5) });
	settings.at(settingHandle::m_setting.get("RESOLUTION").first())->push(settingHandle::m_setting.get("RESOLUTION").second()->values.getKeys());
	settings.at(settingHandle::m_setting.get("RESOLUTION").first())->setCurrent(settingHandle::m_setting.get("RESOLUTION").second()->current);

	
	settings.insert({ settingHandle::m_setting.get("FPS").first(),
		new DropDownBox(sf::Vector2f(200.f, 40.f),sf::Vector2f(position.x + 200.f, position.y - 100.f),sf::Color(100,100,150),systemHandle::getFont(),18,5) });

	//auto k = settingHandle::m_setting.begin().first();
	//auto j = (settingHandle::m_setting.begin() + 0).first();
	settings[settingHandle::m_setting.get("FPS").first()]->push(settingHandle::m_setting.get("FPS").second()->values.getKeys());
	settings[settingHandle::m_setting.get("FPS").first()]->setCurrent(settingHandle::m_setting.get("FPS").second()->current);
}

void SettingState::reinit()
{

}


void SettingState::updateButtonActive()
{
	for (auto& i : buttons)
		if (i.second->isActive())
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
		std::ofstream OUTFILE("resource/init/window.init");
		if (OUTFILE.is_open())
		{
			OUTFILE << settingHandle::title << "\n" << "RESOLUTION " << settingHandle::m_setting.at("RESOLUTION")->current << "\n"
				<< "FPS " << settingHandle::m_setting.at("FPS")->current;
			OUTFILE.close();
		}
		else
			logWARNING("couldn't save settings at: resource/init/window.init");

		sf::Vector2u size = std::get<sf::Vector2u>(settingHandle::getCurrentSetting("RESOLUTION"));
		settingHandle::window->create(sf::VideoMode(size.x, size.y), settingHandle::title, sf::Style::Close | sf::Style::Titlebar);
		settingHandle::window->setFramerateLimit(std::get<unsigned int>(settingHandle::getCurrentSetting("FPS")));

		State::states->pop();
		State::states->top()->reinit();
		delete this;
	}
}
