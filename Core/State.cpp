#include "pch.h"
#include "State.h"
#include "systemHandle.h"

State::State()
{

}

State::~State()
{

}

void State::initBackground(const std::string filePath)
{
	if (systemHandle::getTexture(filePath))
	{
		this->sprite.setTexture(*systemHandle::getTexture(filePath));
		float scale = systemHandle::getWindow()->getSize().y / this->sprite.getGlobalBounds().getSize().y;
		this->sprite.setScale(scale, scale);
	}
	else
		logWARNING("couldn't find texture: " + filePath);
}


std::stack<State*>* State::states = nullptr;
