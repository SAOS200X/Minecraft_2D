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

	if (view)
		delete view;

	for (auto& i : systemHandle::textures)
		delete i.second;
	for (auto& i : systemHandle::fonts)
		delete i;

	while (!states.empty())
	{
		delete states.top();
		states.pop();
	}
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

	initSettingHandle();
	initDefaultWindow();
	initWindow(m_path::path_window);

	initSystemHandle();
	initTextures();
	initFonts();
	initState();
}

void Core::initDefault()
{
	srand(static_cast<unsigned>(time(0)));
	defaultWindow = nullptr;
	window = nullptr;
	view = nullptr;
	dt = 0;
	clock.restart();
}


void Core::initSettingHandle()
{
	settingHandle::loadSetting(m_path::path_setting);
	settingHandle::title = "Minecraft 2D";
	settingHandle::m_setting.at("RESOLUTION")->current = 3;
	settingHandle::m_setting.at("FPS")->current = 0;

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
			logWARNING("file corrupted: " + filePath);
			window = defaultWindow;
		}
	}
	else
	{
		logWARNING("couldn't open file: " + filePath);
		window = defaultWindow;
	}

	view = new sf::View(0.5f * window->getSize(), 1.f * window->getSize());
	settingHandle::window = this->window;
}

void Core::initSystemHandle()
{
	systemHandle::window = this->window;
	systemHandle::view = this->view;
	systemHandle::dt = &this->dt;
}

void Core::initTextures()
{
	systemHandle::loadTexture(m_path::bg_main);
	systemHandle::loadTexture(m_path::bg_setting);
	systemHandle::loadTexture(m_path::bg_singleplayer);
	systemHandle::loadTexture(m_path::bg_newworld);
	systemHandle::loadTexture(m_path::button_blank);
	systemHandle::loadTexture(m_path::button_option);
	systemHandle::loadTexture(m_path::button_quit);
	systemHandle::loadTexture(m_path::button_singleplayer);
	systemHandle::loadTexture(m_path::tilesheet);
	systemHandle::loadTexture(m_path::itemsheet);
}

void Core::initFonts()
{
	//systemHandle::loadFont(m_path::font_0);
	systemHandle::loadFont(m_path::font_1);


	text.setFont(*systemHandle::getFont());
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
	updateKeyPressed();

	if (!states.empty())
		states.top()->update();

	updateTextDebug();
}

void Core::updateKeyPressed()
{
	_MY_DEBUG_

	for (unsigned int i = 0; i < 75; i++)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(i)))
		{
			if (systemHandle::KeyState[sf::Keyboard::Key(i)] == systemHandle::state::release)
				systemHandle::KeyState[sf::Keyboard::Key(i)] = systemHandle::state::pressed;
			else if (systemHandle::KeyState[sf::Keyboard::Key(i)] == systemHandle::state::pressed)
				systemHandle::KeyState[sf::Keyboard::Key(i)] = systemHandle::state::hold;
		}

	for (unsigned int i = 0; i < 2; i++)
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button(i)))
		{
			if (systemHandle::MouseState[sf::Mouse::Button(i)] == systemHandle::state::release)
				systemHandle::MouseState[sf::Mouse::Button(i)] = systemHandle::state::pressed;
			else if (systemHandle::MouseState[sf::Mouse::Button(i)] == systemHandle::state::pressed)
				systemHandle::MouseState[sf::Mouse::Button(i)] = systemHandle::state::hold;
		}
}

void Core::updateInput()
{
	dt = clock.getEslapseTime();
	clock.restart();

	systemHandle::mousePosWindow = sf::Mouse::getPosition(*window);
	systemHandle::mousePosView = window->mapPixelToCoords(systemHandle::mousePosWindow, *view);

	if (systemHandle::utf)
		systemHandle::utf = 0;

	while (window->pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed)
			window->close();
		else if (ev.type == sf::Event::KeyReleased)
			systemHandle::KeyState[ev.key.code] = systemHandle::state::release;
		
		if (ev.type == sf::Event::MouseButtonReleased)
			systemHandle::MouseState[ev.mouseButton.button] = systemHandle::state::release;

		if (ev.type == sf::Event::TextEntered)
		{
			if (ev.text.unicode <= 127)
				systemHandle::utf = ev.text.unicode;
		}
	}

}

void Core::updateTextDebug()
{
	auto m = static_cast<sf::Vector2i>(systemHandle::getMousePosView());
	auto n = systemHandle::getMousePosWindow();
	std::stringstream ss;
	ss << n.x << " " << n.y;
	text.setCharacterSize(16);
	text.setOutlineThickness(2.f);
	text.setString(ss.str());
	text.setPosition(n.x + 10.f, n.y + 10.f);
}

void Core::render()
{
	window->clear();

	if (!states.empty())
		states.top()->render(window);
	window->draw(text);

	window->display();
}

