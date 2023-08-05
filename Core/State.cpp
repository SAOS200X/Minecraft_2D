#include "pch.h"
#include "State.h"

State::State()
{
	
}

State::~State()
{
}

std::stack<State*>* State::states = nullptr;
