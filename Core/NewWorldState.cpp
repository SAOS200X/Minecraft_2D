#include "pch.h"
#include "NewWorldState.h"
#include "systemHandle.h"
#include "SinglePlayerState.h"


NewWorldState::NewWorldState()
{
	this->initBackground(m_path::bg_newworld);
	initTextBoxs();
	initButton();
}

NewWorldState::~NewWorldState()
{
	for (auto& i : textBoxs)
		delete i.second;
	for (auto& i : buttons)
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

	for (auto& i : buttons)
		i.second->update(static_cast<sf::Vector2f>(systemHandle::getMousePosWindow()),systemHandle::isButtonPressed(sf::Mouse::Left));

	updateButtonActive();
}

void NewWorldState::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
	for (auto& i : textBoxs)
		i.second->render(target);
	for (auto& i : buttons)
		i.second->render(target);
}

void NewWorldState::initTextBoxs()
{
	textBoxs.insert({ "NAME", new TextBox(sf::Vector2f(400.f, 40.f), sf::Vector2f(systemHandle::getWindow()->getSize().x / 2.f, systemHandle::getWindow()->getSize().y * 2.f / 7.f),
		sf::Color::Black, systemHandle::getFont(), 24) });

	textBoxs.insert({ "SEED", new TextBox(sf::Vector2f(150.f, 40.f), sf::Vector2f(systemHandle::getWindow()->getSize().x / 2.f, systemHandle::getWindow()->getSize().y * 3.f / 7.f),
		sf::Color::Black, systemHandle::getFont(), 24) });
}

void NewWorldState::initButton()
{
	buttons.insert({ "CREATE",new Button(systemHandle::getTexture(m_path::button_blank), sf::Vector2f(systemHandle::getWindow()->getSize().x / 2.f - 300.f, systemHandle::getWindow()->getSize().y * 6.f / 7.f), 
		systemHandle::getFont(), 24, "Create New World") });

	buttons.insert({ "CANCEL",new Button(systemHandle::getTexture(m_path::button_blank), sf::Vector2f(systemHandle::getWindow()->getSize().x / 2.f + 300.f, systemHandle::getWindow()->getSize().y * 6.f / 7.f),
		systemHandle::getFont(), 24, "Cancel") });
}

void NewWorldState::updateButtonActive()
{
	for (auto& i : buttons)
		if (i.second->isButtonPressed())
		{
			if (i.first == "CREATE")
				createNewWorld();
			else if (i.first == "CANCEL")
			{
				this->states->pop();
				delete this;
			}
			return;
		}
}

void NewWorldState::createNewWorld()
{
	auto i = static_cast<SinglePlayerState*>(states->_Get_container().at(states->size() - 2));
	if (textBoxs.at("NAME")->getString().size() && (std::find(i->saves.begin(), i->saves.end(), textBoxs.at("NAME")->getString()) == i->saves.end()))
	{
		this->states->pop();
		std::string filePath = "resource/saves/" + textBoxs.at("NAME")->getString() + ".save";

		if (!textBoxs.at("SEED")->getString().size())
			textBoxs.at("SEED")->setString(rand());

		std::ofstream OUTFILE(m_path::save_global);
		if (OUTFILE.is_open())
		{
			OUTFILE << i->saves.size() + 1 << "\n";

			for (auto& j : i->saves)
				OUTFILE << j.getSaves().name << "\n" << j.getSaves().filePath << "\n" << j.getSaves().date << "\n" << j.getSaves().seed << "\n";

			OUTFILE << textBoxs.at("NAME")->getString() << "\n" << filePath << "\n" << time(0) << "\n" << textBoxs.at("SEED")->getString() << "\n";

			OUTFILE.close();
		}
		
		OUTFILE.open(filePath);
		if (OUTFILE.is_open())
		{
			OUTFILE << time(0) << " " << 0 << "\n";
			OUTFILE << textBoxs.at("SEED")->getString() << "\n";
			OUTFILE.close();
		}

		i->loadGlobalSave(m_path::save_global);

		delete this;
	}
}
