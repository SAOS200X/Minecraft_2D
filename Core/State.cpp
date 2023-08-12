#include "pch.h"
#include "State.h"

State::State()
{
	texture = nullptr;
}

State::~State()
{
	if (texture)
		delete texture;
}


std::stack<State*>* State::states = nullptr;
