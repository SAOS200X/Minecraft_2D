#include "pch.h"
#include "Core.h"
#include "systemHandle.h"
#include "settingHandle.h"

Core::Core()
{ 
	init();
}

Core::~Core()
{
	if (defaultWindow)
		delete defaultWindow;
	else
		delete window;

	while (!states.empty())
	{
		delete states.top();
		states.pop();
	}

	delete font;
}

void Core::run()
{
	while (window->isOpen() && !states.empty())
	{
		update();
		render();
	}
}

////////////////////////////////////////////////////// INIT ////////////////////////////////////////////////////////

void Core::init()
{
	initDefault();
	initFont(m_macro::font_0);



	initSettingHandle();
	initDefaultWindow();
	initWindow(m_macro::init_1);

	initSystemHandle();
	initState();
}

void Core::initDefault()
{
	defaultWindow = nullptr;
	window = nullptr;
	view = nullptr;
	dt = 0;
	font = nullptr;
	clock.restart();
}

void Core::initFont(std::string filePath)
{
	this->font = new sf::Font;
	if (!font->loadFromFile(filePath))
		logWARNING("couldn't open file: " + filePath);

	text.setFont(*font);
}

void Core::initSettingHandle()
{
	settingHandle::loadSetting(m_macro::init_0);
	settingHandle::title = m_macro::name_0;
	settingHandle::m_setting.at(m_macro::name_1)->current = 3;
	settingHandle::m_setting.at(m_macro::name_2)->current = 0;

}

void Core::initDefaultWindow()
{
	defaultWindow = new sf::RenderWindow(sf::VideoMode(800, 600),
		"Default", sf::Style::Close | sf::Style::Titlebar);
	defaultWindow->setFramerateLimit(30);
}

void Core::initWindow(std::string filePath)
{
	_MY_DEBUG_

	std::ifstream INFILE(filePath);
	if (INFILE.is_open())
	{
		if (INFILE.good())
		{
			std::string title, name;
			unsigned int index;

			sf::Vector2u size(800, 600);
			unsigned int fps = 30;


			getline(INFILE, title);
			if (!title.empty())
				settingHandle::title = title;

			INFILE >> name >> index;
			if (settingHandle::m_setting.contain(name))
			{
				settingHandle::m_setting.at(name)->current = index;
				size = std::get<sf::Vector2u>(settingHandle::m_setting.at(name)->values.at(index));
			}

			INFILE >> name >> index;
			if (settingHandle::m_setting.contain(name))
			{
				settingHandle::m_setting.at(name)->current = index;
				fps = std::get<unsigned int>(settingHandle::m_setting.at(name)->values.at(index));
			}

			window = new sf::RenderWindow(sf::VideoMode(size.x, size.y),
				settingHandle::title, sf::Style::Close | sf::Style::Titlebar);
			defaultWindow->setFramerateLimit(fps);

			delete defaultWindow;
			defaultWindow = nullptr;

			INFILE.close();
		}
		else
		{
			logERROR("file corrupted: " + filePath);
			window = defaultWindow;
		}
	}
	else
	{
		logERROR("couldn't open file: " + filePath);
		window = defaultWindow;
	}

	settingHandle::window = this->window;
}

void Core::initSystemHandle()
{
	systemHandle::window = this->window;
	systemHandle::font = this->font;
	systemHandle::dt = &this->dt;
}

void Core::initState()
{
	states.push(new MainMenuState());

	State::states = &this->states;
}



//////////////////////////////////////////////////////// UPDATE ////////////////////////////////////////////////////////

void Core::update()
{
	updateInput();

	if (!states.empty())
		states.top()->update();

	updateTextDebug();
}

void Core::updateInput()
{
	dt = clock.restart().asMilliseconds();

	while (window->pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed)
			window->close();
		else if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
		{
			if (State::states->size() > 1)
			{
				delete State::states->top();
				State::states->pop();
			}
		}
	}

	systemHandle::mousePosWindow = sf::Mouse::getPosition(*window);

}

void Core::updateTextDebug()
{
	auto m = systemHandle::getMousePosWindow();
	std::stringstream ss;
	ss << m.x << " " << m.y;
	text.setCharacterSize(16);
	text.setOutlineThickness(2.f);
	text.setString(ss.str());
	text.setPosition(m.x + 10.f, m.y + 10.f);
}

void Core::render()
{
	window->clear();

	if (!states.empty())
		states.top()->render(window);
	window->draw(text);

	window->display();
}

