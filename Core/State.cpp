#include "pch.h"
#include "State.h"
#include "systemHandle.h"

State::State()
{
	texture = nullptr;
}

State::~State()
{
	if (texture)
		delete texture;
}

void State::initBackground(const std::string filePath)
{
	this->sprite.setTexture(*systemHandle::getTexture(filePath));
	float scale = systemHandle::getWindow()->getSize().y / this->sprite.getGlobalBounds().getSize().y;
	this->sprite.setScale(scale, scale);
}


std::stack<State*>* State::states = nullptr;
