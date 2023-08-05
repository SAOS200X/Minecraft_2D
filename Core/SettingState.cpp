#include "pch.h"
#include "SettingState.h"

SettingState::SettingState()
{
	initTexture("resource/image/dirt.jpg");
	initDropBox();
}

SettingState::~SettingState()
{
	for (auto& i : settings)
		delete i.second;
}

void SettingState::update()
{
	for (auto& i : settings)
		i.second->update(static_cast<sf::Vector2f>(s_System::getMousePosWindow()),*s_System::getDeltaTime());
}

void SettingState::updateButtonActive()
{
}

void SettingState::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
	for (auto& i : settings)
		i.second->render(target);
}

void SettingState::initTexture(std::string filePath)
{
	this->texture = new sf::Texture;
	if (!this->texture->loadFromFile(filePath))
		logWARNING("Couldn't open file: " + filePath);

	this->sprite.setTexture(*this->texture);
	this->sprite.scale(1.5, 1.5);
}

void SettingState::initButton()
{
}

void SettingState::initDropBox()
{
	settings.insert({ "RESOLUTION", new DropDownBox(sf::Vector2f(200.f,40.f),sf::Vector2f(200.f,100.f),sf::Color(100,100,150),s_System::getFont(),18,5) });
	settings["RESOLUTION"]->push("1920x1080");
	settings["RESOLUTION"]->push("1600x900");
	settings["RESOLUTION"]->push("1366x768");
	settings["RESOLUTION"]->push("1280x720");
	settings["RESOLUTION"]->push("1000x750");
	settings["RESOLUTION"]->push("800x600");
	settings["RESOLUTION"]->setCurrent(3);


}
